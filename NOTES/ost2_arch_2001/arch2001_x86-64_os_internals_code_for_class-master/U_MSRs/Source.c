// Created by Xeno Kovah in 2021 for OpenSecurityTraining2 Architecture 2001 class
// This Source Code Form is subject to the terms of  the Mozilla Public License, v. 2.0

#include <stdio.h>

void main() {
	int cpuInfo[4] = { 0 };
	__cpuidex(cpuInfo, 0x80000001, 0);
	if (((cpuInfo[3] >> 20) & 1) || ((cpuInfo[3] >> 29) & 1)) {
		__int64 out = __readmsr(0xC0000080);
		printf("IA32_EFER = 0x%016llx\n", out);
		if ((out >> 8) & 1) printf("IA32_EFER.LME = 1\n");
		if ((out >> 10) & 1) printf("IA32_EFER.LMA = 1\n");
	}
	else {
		printf("IA32_EFER not supported on this platform\n");
	}
}
