;
; Author: Manuel Ángel Suárez Álvarez
; E-mail Manuel_Angel99@outlook.com
; Created: 2016-08-11 13:14:53
; 
; File: crti.asm
; Description: Puts the contents of crtbegin.o init and end content here
;

section .init
global _init:function
_init:
	push ebp
	mov ebp, esp
.end:

section .fini
global _fini:function
_fini:
	push ebp
	mov ebp, esp
.end: