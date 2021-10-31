; Author: Abhinav Thakur
; Email : compilepeace@gmail.com
;
; Description: A template program to call Glibc functions from ASM code
;
; Input : None
; Output: printf statement
;
; Compile & run (disabling PIE)
; nasm calling_libc_from_asm.asm -f elf64 -o printf.o
; gcc -no-pie printf.o
; ./a.out
;
; Compile & run (write PIE code using relative addressing)
;
;
; Mark printf function as 'external' entity.
; Further calling Glibc functions from our custom assembly


    section .data
format_string: 
    db "printf@libc says hi! returning: %d", 0xa, 0        ; printf format string with a newline (0xa) and NULL terminator (0x0)


    section .text
    global main
    extern printf


hilibc:
    ; function prologue
    push rbp
    mov rbp, rsp
    
    ; printf ("printf@libc says hi!, returning: %d\n", 0x7);
    lea rdi, [format_string]
    mov esi , 0x7
    mov rax, 0      ; 0 floating point parameters (specified by rax)
    call printf

    mov eax, 0x7    ; hilibc() should return 0x7
    
    ; function epilogue
    mov rsp, rbp    ; these 2 instructions are actually 'leave' instruction
    pop rbp
    ret


main:
    ; hilibc()
    call hilibc

    ; exit(0xa)
    mov eax, 60
    mov edi, 0xa
    syscall

