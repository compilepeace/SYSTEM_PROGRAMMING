//UserspaceSegmentRegisters.c: Code to interpret userspace segment selectors
//Instructions Learned: MOV from Segment Registers to memory
//Written by Xeno Kovah, Jan. 9th 2010
//Originally for use with MITRE Institute Intermediate x86 Class
//Licensed under Creative Commons Share Alike license.
//full details available here: http://creativecommons.org/licenses/by-sa/3.0
//P.s. Don't comment on the efficency or style of the code, it's tutorial code! :P

// Modified by Xeno Kovah in 2021 for OpenSecurityTraining2 Architecture 2001 class
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0

#include <stdio.h>

void SelectorPrint(char* regName, unsigned short reg) {
    printf("U_SegRegs32: %s Register = 0x%02x\n", regName, reg);
    printf("U_SegRegs32: %s Register RPL = %x, Table Indicator = %s, Index = 0x%04x\n", regName, (reg & 3), ((reg >> 2) & 1) ? "1 (LDT)" : "0 (GDT)", ((reg >> 3) & 0x1FFF));
}

int main() {
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

    return 0x0ddba11;
}