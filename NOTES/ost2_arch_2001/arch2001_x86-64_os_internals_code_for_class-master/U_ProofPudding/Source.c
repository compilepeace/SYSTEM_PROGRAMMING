// Created by Xeno Kovah in 2021 for OpenSecurityTraining2 Architecture 2001 class
// This Source Code Form is subject to the terms of 
// the Mozilla Public License, v. 2.0

extern unsigned char* asm_func();

#include <stdio.h>

void main()
{
	unsigned char* bla = 0;
	bla = asm_func();
	printf("The proof is in the pudding!\n");
	printf("byte in asm_test() @ bla (0x%p) = 0x%02x", bla, *bla);
}