;
; Author: Manuel Ángel Suárez Álvarez
; E-mail Manuel_Angel99@outlook.com
; Created: 2016-08-11 13:14:53
; 
; File: crti.asm
; Description: Puts the contents of crtbegin.o init and end content here
;

section .init
global constructors_init:function (constructors_init.end - constructors_init)
constructors_init:
	push ebp
	mov ebp, esp
.end:

section .fini
global fini:function (fini.end - fini)
fini:
	push ebp
	mov ebp, esp
.end: