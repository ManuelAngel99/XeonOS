;
; Author: Manuel Ángel Suárez Álvarez
; E-mail Manuel_Angel99@outlook.com
; Created: 2016-08-13 20:49:35
; 
; File: load_idt.asm
; Description: Implements the laod_idt function
;

global load_idt 		; Allow C to link to this
extern idt_pointer		; Says the idt_pointer is defined elsewhere

load_idt:
	lidt [idt_pointer] 	; Load the IDT with the 'idt_pointer'
	sti 				; Enable interrupts
ret