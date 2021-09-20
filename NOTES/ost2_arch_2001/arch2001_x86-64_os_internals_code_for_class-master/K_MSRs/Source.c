// Created by Xeno Kovah in 2021 for OpenSecurityTraining2 Architecture 2001 class
// This Source Code Form is subject to the terms of 
// the Mozilla Public License, v. 2.0

#include <ntddk.h>
#include <wdf.h>
DRIVER_INITIALIZE DriverEntry;
EVT_WDF_DRIVER_DEVICE_ADD K_MSRsEvtDeviceAdd;

// Basically everything except this function is just boilerplate
// copied from the KMDF Hello World to make a basic kernel driver
void CodeOfConsequence() {
    int cpuInfo[4] = { 0 };
    __cpuidex(cpuInfo, 0x80000001, 0);
    if (((cpuInfo[3] >> 20) & 1) || ((cpuInfo[3] >> 29) & 1)) {
        __int64 out = __readmsr(0xC0000080);
        KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "K_MSRs: IA32_EFER = 0x%016llx\n", out));
        if ((out >> 8) & 1)
            KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "K_MSRs: IA32_EFER.LME = 1\n"));
        if ((out >> 10) & 1)
            KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "K_MSRs: IA32_EFER.LMA = 1\n"));
    }
    else {
        KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "IA32_EFER not supported on this platform\n"));
    }
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

    KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "K_MSRs: DriverEntry\n"));

    // Initialize the driver configuration object to register the
    // entry point for the EvtDeviceAdd callback, K_MSRsEvtDeviceAdd
    WDF_DRIVER_CONFIG_INIT(&config,
        K_MSRsEvtDeviceAdd
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
K_MSRsEvtDeviceAdd(
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
    KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "K_MSRs: K_MSRsEvtDeviceAdd\n"));

    // Actual code of consequence
    CodeOfConsequence();

    // Create the device object
    status = WdfDeviceCreate(&DeviceInit,
        WDF_NO_OBJECT_ATTRIBUTES,
        &hDevice
    );
    return status;
}
