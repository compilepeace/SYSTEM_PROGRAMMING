;; Created by Xeno Kovah in 2021 for OpenSecurityTraining2 Architecture 2001 class
;; This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0

.code
asm_func_OS_popup PROC PUBLIC
   mov eax, 564D5868h  ; Move the VMWare magic number into eax
   mov cx, 12h         ; Command 0x12 = 'Popup "OS not found" dialog'
   mov dx, 5658h       ; The actual IO port number

   in eax, dx          ; Read data in from the IO port to execute the command

   ret
asm_func_OS_popup ENDP

asm_func_get_clipboard_text_len PROC PUBLIC
   mov eax, 564D5868h  ; Move the VMWare magic number into eax
   mov cx, 06h         ; Command 0x06 = Get clipboard text length
   mov dx, 5658h       ; The actual IO port number

   in eax, dx          ; Read data in from the IO port to execute the command

   ret
asm_func_get_clipboard_text_len ENDP

asm_func_get_clipboard_text PROC PUBLIC
   mov eax, 564D5868h  ; Move the VMWare magic number into eax
   mov cx, 07h         ; Command 0x07 = Get 4 bytes of clipboard text
   mov dx, 5658h       ; The actual IO port number

   in eax, dx          ; Read data in from the IO port to execute the command

   ret
asm_func_get_clipboard_text ENDP

end