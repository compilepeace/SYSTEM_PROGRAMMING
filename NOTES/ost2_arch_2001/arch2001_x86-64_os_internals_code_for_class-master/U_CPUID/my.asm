;; Created by Xeno Kovah in 2021 for OpenSecurityTraining2 Architecture 2001 class
;; This Source Code Form is subject to the terms of 
;; the Mozilla Public License, v. 2.0

.code
is_cpuid_supported PROC PUBLIC
   ; The manual says:
   ; "The ID flag (bit 21) in the EFLAGS register indicates support for the CPUID instruction. 
   ; If a software procedure can set and clear this flag, the processor executing the procedure 
   ; supports the CPUID instruction.""
   ; So let's see if we can set or clear the ID flag
   pushfq                   ; Save RFLAGS to stack
   mov r15, [rsp]           ; Store a copy of the original flags in r15 to restore later
   bts qword ptr [rsp], 21  ; Copy original bit 21 into carry flag, and set bit 21
   jnc try_write_rflags     ; If original bit 21 was zero, we've modified bit 21 and are ready to try writing to RFLAGS
   btr qword ptr [rsp], 21  ; Else, if original bit 21 was 1, our bts instruction didn't change it, 
                            ; so reset bit 21 to change it
try_write_rflags:
   popfq                    ; Try to write a change to RFLAGS

   mov rax, 1               ; Presume success, and change rax if necessary
   
   pushfq                   ; Save RFLAGS again
   cmp [rsp], r15           ; CMP (SUB) the current and original flags. If they are the same, ZF=1, otherwise ZF=0
   jnz cleanup              ; If what's was originally in the register != what's there now, ZF=0 and we changed ID flag, so return 1
   mov rax, 0               ; Else they're the same, so no change, so we couldn't alter ID flag and CPUID isn't supported, so return 0
cleanup:
   mov [rsp], r15           ; Restore the original RFLAGS from r15
   popfq                    ; Write original RFLAGS back, and balance the stack
   ret
is_cpuid_supported ENDP

call_cpuid PROC PUBLIC eax_in_val:DWORD, ecx_in_val:DWORD, eax_out_ptr:QWORD, ebx_out_ptr:QWORD, ecx_out_ptr:QWORD, edx_out_ptr:QWORD
   ; Since masm doen't seem to handle the x86-64 
   ; calling convention with variables properly when trying to use parameters
   ; (or I can't find the right syntax),
   ; I just need to grab stuff from the registers myself I guess...
   mov r10, rcx                 ; eax_in_val
   mov r11, rdx                 ; ecx_in_val
   mov r12, r8                  ; eax_out_ptr
   mov r13, r9                  ; ebx_out_ptr
   mov r14, qword ptr [rsp+30h] ; ecx_out_ptr
   mov r15, qword ptr [rsp+38h] ; edx_out_ptr

   mov rax, r10
   mov rcx, r11
   cpuid

   mov dword ptr [r12], eax
   mov dword ptr [r13], ebx
   mov dword ptr [r14], ecx
   mov dword ptr [r15], edx
   ret
call_cpuid ENDP 
end
