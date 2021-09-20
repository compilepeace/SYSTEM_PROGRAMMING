// Created by Xeno Kovah in 2021 for OpenSecurityTraining2 Architecture 2001 class
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0

#include <ntddk.h>
#include <wdf.h>
DRIVER_INITIALIZE DriverEntry;
EVT_WDF_DRIVER_DEVICE_ADD K_SegRegs32EvtDeviceAdd;

void SelectorPrint(char* regName, unsigned short reg) {
    KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "K_SegRegs32: %s Register = 0x%02x\n", regName, reg));
    KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "K_SegRegs32: %s Register RPL = %x, Table Indicator = %s, Index = 0x%04x\n", regName, (reg & 3), ((reg >> 2) & 1) ? "1 (LDT)" : "0 (GDT)", ((reg >> 3) & 0x1FFF)));
}

// Basically everything below this function is just boilerplate
// copied from the KMDF Hello World to make a basic kernel driver
void CodeOfConsequence() {
    unsigned short myCS, myDS, myES, myFS, myGS, mySS;

    //Move the segment registers into the C variables
    __asm {
        mov myCS, cs;
        mov myDS, ds;
        mov myES, es;
        mov myFS, fs;
        mov myGS, gs;
        mov mySS, ss;
    }
    SelectorPrint("CS", myCS);
    SelectorPrint("SS", mySS);
    SelectorPrint("DS", myDS);
    SelectorPrint("ES", myES);
    SelectorPrint("FS", myFS);
    SelectorPrint("GS", myGS);
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

    KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "K_SegRegs32: DriverEntry\n"));

    // Initialize the driver configuration object to register the
    // entry point for the EvtDeviceAdd callback, K_SegRegs32EvtDeviceAdd
    WDF_DRIVER_CONFIG_INIT(&config,
        K_SegRegs32EvtDeviceAdd
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
K_SegRegs32EvtDeviceAdd(
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
    KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "K_SegRegs32: K_SegRegs32EvtDeviceAdd\n"));

    // Actual code of consequence
    CodeOfConsequence();

    // Create the device object
    status = WdfDeviceCreate(&DeviceInit,
        WDF_NO_OBJECT_ATTRIBUTES,
        &hDevice
    );
    return status;
}