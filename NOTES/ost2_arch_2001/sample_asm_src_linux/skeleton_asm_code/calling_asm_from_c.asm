; Author: Abhinav Thakur
; Email : compilepeace@gmail.com
;
; Description: A template program to call Glibc functions from ASM code
;
; Input : None
; Output: define functions (test)
;
; Compile as object code
; nasm -f elf64 -g dwarf2 calling_asm_from_c.asm
; gcc main.c calling_asm_from_c.o -o main



    segment .data
banner: 
    db "hello, this is a basic skeleton program", 0xa, 0x0

    segment .text
    global func1
    global func2

func1:
    ; function prologue
    push rbp
    mov rbp, rsp

    ; useful code starts here
    mov eax, 0x7    
    
    ; function epilogue
    mov rsp, rbp    ; below 2 lines are indeed 'leave' instructions.
    pop rbp
    ret

func2:
    push rbp
    mov rbp, rsp
    mov eax, 8
    leave
    ret
