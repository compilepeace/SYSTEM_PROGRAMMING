#include <stdio.h>
#include <string.h>

extern int is_cpu_supported();
extern int call_cpuid();

int main () {

    int eax_in, ecx_in, eax_out, ebx_out, ecx_out, edx_out;
    int ret;
    char brand_string[13];

    if ( !is_cpu_supported() ) {
        fprintf (stderr, "cpuid instruction not supported\n");
    }
    else {
        /* 
            Identify Processor Brand String 
        */
        eax_in = ecx_in = 0;
        ret = call_cpuid (eax_in, ecx_in, &eax_out, &ebx_out, &ecx_out, &edx_out);
        //fprintf (stderr, "cpuid returned: %d\n", ret);
        fprintf (stderr, "Maximum input value for CPUID information: %d\n", eax_out);
        memcpy (&brand_string[0], &ebx_out, 4);
        memcpy (&brand_string[4], &edx_out, 4);
        memcpy (&brand_string[8], &ecx_out, 4);
        brand_string[12] = '\x00';
        fprintf (stderr, "Brand string: %s\n", brand_string);
    
        /*
            Identify Processor Security Support
                Bit 02: supports SGX (Software Guard extension) if set to 1.
                Bit 07: supports SMEP (Supervisor-Mode Execution Prevention) if set to 1.
                Bit 20: supports SMAP (Supervisor-Mode Access Prevention) if set to 1.
        */
        eax_in = 7;
        ecx_in = 0;
        ebx_out = 0xff;
        call_cpuid (eax_in, ecx_in, &eax_out, &ebx_out, &ecx_out, &edx_out);

        if ( (ebx_out >> 2)  & 1)   fprintf (stderr, "[+] SGX supported\n");
        else                        fprintf (stderr, "[-] Doesn't support SGX\n");
        if ( (ebx_out >> 7)  & 1)   fprintf (stderr, "[+] SMEP supported\n");
        else                        fprintf (stderr, "[-] Doesn't support SMEP\n");
        if ( (ebx_out >> 20) & 1)   fprintf (stderr, "[+] SMAP supported\n");
        else                        fprintf (stderr, "[-] Doesn't support SMAP\n");
        fprintf (stderr, "cpuid done. Bye !\n");
    }
}