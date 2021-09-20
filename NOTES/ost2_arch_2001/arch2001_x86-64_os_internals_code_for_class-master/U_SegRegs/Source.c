//UserspaceSegmentRegisters.c: Code to interpret userspace segment selectors
//Instructions Learned: MOV from Segment Registers to memory
//Written by Xeno Kovah, Jan. 9th 2010
//Originally for use with MITRE Institute Intermediate x86 Class
//Licensed under Creative Commons Share Alike license.
//full details available here: http://creativecommons.org/licenses/by-sa/3.0
//P.s. Don't comment on the efficency or style of the code, it's tutorial code! :P

// Modified by Xeno Kovah in 2021 for OpenSecurityTraining2 Architecture 2001 class
// This Source Code Form is subject to the terms of 
// the Mozilla Public License, v. 2.0

#include <stdio.h>

extern void read_cs(unsigned short* cs);
extern void read_ds(unsigned short* ds);
extern void read_ss(unsigned short* ss);
extern void read_es(unsigned short* es);
extern void read_fs(unsigned short* fs);
extern void read_gs(unsigned short* gs);

void SelectorPrint(char* regName, unsigned short reg) {
    printf("U_SegRegs: %s Register = 0x%02x\n", regName, reg);
    printf("U_SegRegs: %s Register RPL = %x, Table Indicator = %s, Index = 0x%04x\n", regName, (reg & 3), ((reg >> 2) & 1) ? "1 (LDT)" : "0 (GDT)", ((reg >> 3) & 0x1FFF));
}

int main() {
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

    return 0x0ddba11;
}