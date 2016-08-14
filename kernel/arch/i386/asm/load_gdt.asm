;
; Author: Manuel Ángel Suárez Álvarez
; E-mail Manuel_Angel99@outlook.com
; Created: 2016-08-13 20:16:54
; 
; File: load_gdt.asm
; Description: Changes the refernce to de GDT and then loads it (We need to reload the segment registers)
;

global load_gdt
extern gdt_pointer

load_gdt:
	lgdt [gdt_pointer]	; Load the GDT using the 'gdt_pointer'
	mov ax, 0x10		; 0x10 is the offset in the GDT to our data segment
	mov ds, ax		  	; Point data segment, extra segment, general purpose segments and stack segments
	mov es, ax			; to 0x10	
	mov fs, ax				
	mov gs, ax			
	mov ss, ax			
	jmp 0x08:return_to_c   ; Special a far jump using  0x08 (code segment offset)
return_to_c:
	ret               ; Returns back to the C code