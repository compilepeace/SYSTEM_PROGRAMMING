//ParlorTrick.c: Kernel driver to perform some basic interaction with the vmware IO port
//Heavily dependent on information from https://sites.google.com/site/chitchatvmback/backdoor
//Written by Xeno Kovah, Jan. 16th 2010
//Originally for use with MITRE Institute Intermediate x86 Class
//Licensed under Creative Commons Share Alike license.
//full details available here: http://creativecommons.org/licenses/by-sa/3.0

// Modified by Xeno Kovah in 2021 for OpenSecurityTraining2 Architecture 2001 class
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0

#include <ntddk.h>
#include <wdf.h>
DRIVER_INITIALIZE DriverEntry;
EVT_WDF_DRIVER_DEVICE_ADD VMWarePortIOEvtDeviceAdd;

extern unsigned int asm_func_OS_popup();
extern unsigned int asm_func_get_clipboard_text_len();
extern unsigned int asm_func_get_clipboard_text();

// Basically everything except this function is just boilerplate
// copied from the KMDF Hello World to make a basic kernel driver
void CodeOfConsequence() {
    unsigned int textLen;
    unsigned int textData;
    unsigned char i = 0, j = 0;

    //asm_func_OS_popup();

    // Check what the length of the text is: https://sites.google.com/site/chitchatvmback/backdoor#cmd06h
    textLen = asm_func_get_clipboard_text_len();
    if (textLen == 0xFFFFFFFF) {
        KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "VMWarePortIO: Data in clipboard is not text\n"));
        return;
    }
    else {
        KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "VMWarePortIO: textLen = %#x\n", textLen));
    }

    // For demonstration purposes, limit our printout to a max of 256 characters
    if (textLen > 256) textLen = 256;
    KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "VMWarePortIO: Is this %d bytes of your clipboard data?...\n", textLen));

    // Get the actual clipboard text: https://sites.google.com/site/chitchatvmback/backdoor#cmd07h
    while (i < textLen) {
        textData = asm_func_get_clipboard_text();
        for (j = 0; j < 4; j++) {
            char c = (char)((textData >> j * 8) & 0xFF);
            // If somehow we get non-ASCII chars, just skip them
            if (c < 0x7F) {
                KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "VMWarePortIO: %c\n", c));
            }
            i++;
            if (i == textLen) goto done;
        }
    }
done:
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

    KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "VMWarePortIO: DriverEntry\n"));

    // Initialize the driver configuration object to register the
    // entry point for the EvtDeviceAdd callback, VMWarePortIOEvtDeviceAdd
    WDF_DRIVER_CONFIG_INIT(&config,
        VMWarePortIOEvtDeviceAdd
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
VMWarePortIOEvtDeviceAdd(
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
    KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "VMWarePortIO: VMWarePortIOEvtDeviceAdd\n"));

    // Actual code of consequence
    CodeOfConsequence();

    // Create the device object
    status = WdfDeviceCreate(&DeviceInit,
        WDF_NO_OBJECT_ATTRIBUTES,
        &hDevice
    );
    return status;
}