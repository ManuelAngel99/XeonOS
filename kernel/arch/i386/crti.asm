;
; Author: Manuel Ángel Suárez Álvarez
; E-mail Manuel_Angel99@outlook.com
; Created: 2016-08-11 13:14:53
; 
; File: crti.asm
; Description: Puts the contents of crtbegin.o init and end content here
;

section .init
global init:function (init.end - init)
init:
	push ebp
	mov esp, ebp
.end:

section .fini
global fini:function (fini.end - fini)
fini:
	push ebp
	mov esp, ebp
.end: