;
; Author: Manuel Ángel Suárez Álvarez
; E-mail Manuel_Angel99@outlook.com
; Created: 2016-08-11 13:04:15
; 
; File: crtn.asm
; Description: Sets the contents of crtend.o .init and .fini constents here
;

section .init
	pop ebp
ret

section .fini
	pop ebp
ret