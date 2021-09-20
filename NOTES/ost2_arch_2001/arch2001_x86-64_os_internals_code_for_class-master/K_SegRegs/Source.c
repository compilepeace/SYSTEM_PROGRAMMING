// Created by Xeno Kovah in 2021 for OpenSecurityTraining2 Architecture 2001 class
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0

#include <ntddk.h>
#include <wdf.h>
DRIVER_INITIALIZE DriverEntry;
EVT_WDF_DRIVER_DEVICE_ADD K_SegRegsEvtDeviceAdd;

extern void read_cs(unsigned short* cs);
extern void read_ds(unsigned short* ds);
extern void read_ss(unsigned short* ss);
extern void read_es(unsigned short* es);
extern void read_fs(unsigned short* fs);
extern void read_gs(unsigned short* gs);

void SelectorPrint(char* regName, unsigned short reg) {
    KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "K_SegRegs: %s Register = 0x%02x\n", regName, reg));
    KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "K_SegRegs: %s Register RPL = %x, Table Indicator = %s, Index = 0x%04x\n", regName, (reg & 3), ((reg >> 2) & 1) ? "1 (LDT)" : "0 (GDT)", ((reg >> 3) & 0x1FFF)));
}

// Basically everything below this function is just boilerplate
// copied from the KMDF Hello World to make a basic kernel driver
void CodeOfConsequence() {
    unsigned short cs = 0, ds = 0, ss = 0, es = 0, fs = 0, gs = 0;

    read_cs(&cs);
    SelectorPrint("CS", cs);
    read_ss(&ss);
    SelectorPrint("SS", ss);
    read_ds(&ds);
    SelectorPrint("DS", ds);
    read_es(&es);
    SelectorPrint("ES", es);
    read_fs(&fs);
    SelectorPrint("FS", fs);
    read_gs(&gs);
    SelectorPrint("GS", gs);
}

NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT     DriverObject,
    _In_ PUNICODE_STRING    RegistryPath
)
{
    // NTSTATUS variable to record success or failure
    NTSTATUS status = STATUS_SUCCESS;

    // Allocate the driver configuration object
    WDF_DRIVER_CONFIG config;

    KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "K_SegRegs: DriverEntry\n"));

    // Initialize the driver configuration object to register the
    // entry point for the EvtDeviceAdd callback, K_SegRegsEvtDeviceAdd
    WDF_DRIVER_CONFIG_INIT(&config,
        K_SegRegsEvtDeviceAdd
    );

    // Finally, create the driver object
    status = WdfDriverCreate(DriverObject,
        RegistryPath,
        WDF_NO_OBJECT_ATTRIBUTES,
        &config,
        WDF_NO_HANDLE
    );
    return status;
}

NTSTATUS
K_SegRegsEvtDeviceAdd(
    _In_    WDFDRIVER       Driver,
    _Inout_ PWDFDEVICE_INIT DeviceInit
)
{
    // We're not using the driver object,
    // so we need to mark it as unreferenced
    UNREFERENCED_PARAMETER(Driver);

    NTSTATUS status;

    // Allocate the device object
    WDFDEVICE hDevice;

    // Print "Hello World"
    KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "K_SegRegs: K_SegRegsEvtDeviceAdd\n"));

    // Actual code of consequence
    CodeOfConsequence();

    // Create the device object
    status = WdfDeviceCreate(&DeviceInit,
        WDF_NO_OBJECT_ATTRIBUTES,
        &hDevice
    );
    return status;
}