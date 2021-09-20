// Created by Xeno Kovah in 2021 for OpenSecurityTraining2 Architecture 2001 class
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0

#include <ntddk.h>
#include <wdf.h>
DRIVER_INITIALIZE DriverEntry;
EVT_WDF_DRIVER_DEVICE_ADD CMOS_PortIOEvtDeviceAdd;

// Basically everything except this function is just boilerplate
// copied from the KMDF Hello World to make a basic kernel driver
void CodeOfConsequence() {
    unsigned char cmos[256] = { 0 };
    unsigned char i = 0, j = 0;

    for (i = 0; i < 128; i++) {
        __outbyte(0x70, i);
        cmos[i] = __inbyte(0x71);
        KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "CMOS_PortIO: cmos[%d] = %02x\n", i, cmos[i]));
    }
    for (j = 0; j < 128 ; j++, i++) {
        __outbyte(0x72, j);
        cmos[i] = __inbyte(0x73);
        KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "CMOS_PortIO: cmos[%d] = %02x\n", i, cmos[i]));
    }

    return;
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

    KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "CMOS_PortIO: DriverEntry\n"));

    // Initialize the driver configuration object to register the
    // entry point for the EvtDeviceAdd callback, CMOS_PortIOEvtDeviceAdd
    WDF_DRIVER_CONFIG_INIT(&config,
        CMOS_PortIOEvtDeviceAdd
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
CMOS_PortIOEvtDeviceAdd(
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
    KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "CMOS_PortIO: CMOS_PortIOEvtDeviceAdd\n"));

    // Actual code of consequence
    CodeOfConsequence();

    // Create the device object
    status = WdfDeviceCreate(&DeviceInit,
        WDF_NO_OBJECT_ATTRIBUTES,
        &hDevice
    );
    return status;
}
