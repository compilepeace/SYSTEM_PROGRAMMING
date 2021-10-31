; Author: Abhinav Thakur
; Email : compilepeace@gmail.com
; 
; Description: This module defines functions that checks and
;              uses cpuid instruction to recon system info.
;

    section .text
    global is_cpu_supported
    global call_cpuid

; returns 1 (true) if CPU supports 'cpuid' instruction and 0 (false) otherwise.
; The manual says - 
; "The ID flag (bit 21) in the EFLAGS register indicates support for the CPUID instruction. If a software procedure can
; set and clear this flag, the processor executing the procedure supports the CPUID instruction. The CPUID instruction 
; will cause the invalid opcode exception (#UD) if executed on a processor that does not support it."
;
is_cpu_supported:
    push rbp
    mov rbp, rsp
    
    mov eax, 0x226
    test eax, eax
    jz zero_flag_set
zero_flag_set: 
    mov eax, 0x0

    ; Save the value of RFLAGS.
    ; Modify bit 21 of RFLAGS.
    ; Bitwise AND the saved value with apparently modified value of RFLAGS
    ; to tell if we were able to modify bit 21
    pushfq          ; Save RFLAGS register onto the stack
    mov r15, [rsp]  ; save the a copy of original value of RFLAGS
    
    bts qword [rsp], 21     ; load bit 21 in CF and set bit 21 to 1
    jnc skip                ; If CF was 0, then we are ready to make a change to RFLAGS
    btr qword [rsp], 21     ; else bit 21 was already set to 1, our setting doesn't change
                            ; a thing, so clear it to 0.

skip:
    popfq           ; Try to write the changed value to RFLAGS

    ; Now, checking if 21st bit of RFLAGS was actually modified or not 
    pushfq          ; Save RFLAGS register again to the stack
    mov eax, 1      ; presume success/true 
    sub [rsp], r15 ; AND both the current and saved value of RFLAGS.
    jnz done
    mov eax, 0      ; return failure/false
    
done:
    mov rsp, rbp
    pop rbp
    ret
    

; executes 'cpuid' instruction to check if it is the intel processor
; we are using and some hardware security mechanisms being enforced
; on this arch.
;
; Manual says - 
; "Always begin by testing for the “GenuineIntel,” message in the EBX, EDX, and ECX registers when the CPUID
; instruction is executed with EAX equal to 0. If the processor is not genuine Intel, the feature identification
; flags may have different meanings than are described in Intel documentation."
;
; [See - Vol. 2A 3-215] for the entire table
;
; eax = 0           (identify processor signature string)
; eax = 7, ecx = 0  
;   Bit 02: supports SGX (Software Guard extension) if set to 1.
;   Bit 07: supports SMEP (Supervisor-Mode Execution Prevention) if set to 1.
;   Bit 20: supports SMAP (Supervisor-Mode Access Prevention) if set to 1.
;
; call_cpuid (eax_in_val, ecx_in_val, eax_out_ptr, ebx_out_ptr, ecx_out_ptr, edx_out_ptr);
call_cpuid:
    push rbp
    mov rbp, rsp
    
    ; copy arguments to leftover GPR's 
    ; Saving args are required in Windows x86-64 to implement x86-64 calling conventions
    ; which are supported by default in Linux as a part of x86-64 System V ABI.  
    mov r10, rdi    ; eax_in_val
    mov r11, rsi    ; ecx_in_val
    mov r12, rdx    ; eax_out_ptr
    mov r13, rcx    ; ebx_out_ptr
    mov r14, r8     ; ecx_out_ptr
    mov r15, r9     ; edx_out_ptr

    ; input to cpuid is given by values inside 'eax' and 'ecx'
    mov rax, r10
    mov rcx, r11
    cpuid

    ; put the values returned by cpuid into call_cpuid() arguments 
    ; (i.e. into C variables passed as references)
    mov [r12], eax
    mov [r13], ebx
    mov [r14], ecx
    mov [r15], edx

    mov rsp, rbp
    pop rbp
    ret


