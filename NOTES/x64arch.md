# x64 ARCHITECTURE CHEETSHEET
Notekeeping from [Architecture 2001].

[Architecture 2001]: https://p.ost2.fyi/courses/course-v1:OpenSecurityTraining2+Arch1001_x86-64_Asm+2021_v1/course/


* **cpuid**    
`CPU feature identification` which basically tells if the chip we're running on supports features (like 64-bit mode, hardware virtualization, HyperThreading, thermal monitors etc ).
<br>
It doesn't have operands. Rather it takes `input` as a value preloaded into **eax** (and possibly **ecx**). `Output` are stored in **eax**, **ebx**, **ecx** and **edx**.
<br>
The ID flag (bit 21) in the EFLAGS register indicates support for CPUID instruction. **If a software procedure can *set* or clear this *flag*, the processor executing this procedure supports the CPUID instruction.** To set/clear flags, we need 2 instructions - **PUSHFQ** and **POPFQ** (explained below).
```
see -

eax = 0 
    to identfy processor vendor - Intel, AMD signature string

eax = 07h (ecx = 0)
    Bit 02: supports SGX (Software Guard extension) if set to 1.
    Bit 07: supports SMEP (Supervisor-Mode Execution Prevention) if set to 1.
    Bit 20: supports SMAP (Supervisor-Mode Access Prevention) if set to 1.
```

* **pushfq/popfq**  
The idea is to simply push the EFLAGS register onto the stack, manipulate the value on stack, then pop it back into EFLAGS register.