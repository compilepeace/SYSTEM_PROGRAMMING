;; Created by Xeno Kovah in 2021 for OpenSecurityTraining2 Architecture 2001 class
;; This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0

.code

; Takes a pointer to a 16 bit variable where to write the CS register value
read_cs PROC PUBLIC var1:QWORD
   mov [rcx], cs
   ret
read_cs ENDP

; Takes a pointer to a 16 bit variable where to write the SS register value
read_ss PROC PUBLIC var1:QWORD
   mov [rcx], ss
   ret
read_ss ENDP

; Takes a pointer to a 16 bit variable where to write the DS register value
read_ds PROC PUBLIC var1:QWORD
   mov [rcx], ds
   ret
read_ds ENDP

; Takes a pointer to a 16 bit variable where to write the ES register value
read_es PROC PUBLIC var1:QWORD
   mov [rcx], es
   ret
read_es ENDP

; Takes a pointer to a 16 bit variable where to write the FS register value
read_fs PROC PUBLIC var1:QWORD
   mov [rcx], fs
   ret
read_fs ENDP

; Takes a pointer to a 16 bit variable where to write the GS register value
read_gs PROC PUBLIC var1:QWORD
   mov [rcx], gs
   ret
read_gs ENDP

end