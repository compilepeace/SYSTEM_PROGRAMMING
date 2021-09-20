// Created by Xeno Kovah in 2021 for OpenSecurityTraining2 Architecture 2001 class
// This Source Code Form is subject to the terms of 
// the Mozilla Public License, v. 2.0

#include <stdio.h>

#define uint32 unsigned int

extern char is_cpuid_supported();
extern uint32 call_cpuid(uint32 eax_in_val, uint32 ecx_in_val, uint32* eax_out_ptr, uint32* ebx_out_ptr, uint32* ecx_out_ptr, uint32* edx_out_ptr);

void main()
{
	char id_str[13];
	uint32 ret = 0, eax_in = 0, ecx_in = 0, eax_out = 0, ebx_out = 0, ecx_out = 0, edx_out = 0;
	if (!is_cpuid_supported()) {
		printf("CPUID not supported on this processor. Exiting.");
	}

	eax_in = 0;
	ret = call_cpuid(eax_in, ecx_in, &eax_out, &ebx_out, &ecx_out, &edx_out);
	//printf("call_cpuid returned %d", ret);
	printf("Maximum Input Value for Basic CPUID Information = %d\n", eax_out);
	memcpy(&(id_str[0]), &ebx_out, 4);
	memcpy(&(id_str[4]), &edx_out, 4);
	memcpy(&(id_str[8]), &ecx_out, 4);
	id_str[12] = 0;
	printf("Identity string = %s\n", id_str);

	//Print off some misc security-relevant feature bits
	eax_in = 7;
	ecx_in = 0;
	ret = call_cpuid(eax_in, ecx_in, &eax_out, &ebx_out, &ecx_out, &edx_out);
	// SGX support is bit 2 of EBX
	if ((ebx_out >> 2) & 1) printf("Processor supports SGX\n");
	else printf("Processor doesn't support SGX\n");
	// SMEP support is bit 7 of EBX
	if ((ebx_out >> 7) & 1) printf("Processor supports SMEP\n");
	else printf("Processor doesn't support SMEP\n");
	// SMAP support is bit 20 of EBX
	if ((ebx_out >> 20) & 1) printf("Processor supports SMAP\n");
	else printf("Processor doesn't support SMAP\n");

	////Print off some misc feature bits
	//eax_in = 0x80000008;
	//ecx_in = 0;
	//ret = call_cpuid(eax_in, ecx_in, &eax_out, &ebx_out, &ecx_out, &edx_out);
	////The physical address width, MAXPHYADDR, is reported by CPUID.80000008H:EAX[bits 7:0]
	//printf("MAXPHYADDR = %d\n", eax_out & 0xFF);

	////Print some TLB/cache info
	//eax_in = 0x02;
	//ecx_in = 0;
	//ret = call_cpuid(eax_in, ecx_in, &eax_out, &ebx_out, &ecx_out, &edx_out);
	//printf("CPUID 2 output: eax = 0x%08x\n", eax_out);
	//printf("CPUID 2 output: ebx = 0x%08x\n", ebx_out);
	//printf("CPUID 2 output: ecx = 0x%08x\n", ecx_out);
	//printf("CPUID 2 output: edx = 0x%08x\n", edx_out);
}