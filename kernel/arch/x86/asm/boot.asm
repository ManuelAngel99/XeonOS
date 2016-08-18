;
; Author: Manuel Ángel Suárez Álvarez
; E-mail Manuel_Angel99@outlook.com
; Created: 2016-08-11 11:14:47
; 
; File: boot.asm
; Description: Defines the multiboot header. sets up the stack and calls kernel_main
;

MBOOT_PAGE_ALIGN    equ 1 << 0                                              ; Align the kernel and its modules at a page boundary
MBOOT_MEM_INFO      equ 1 << 1                                              ; Give the kernel some info about the memory map
MBOOT_GRAPHICS      equ 1 << 1                                              ; Set the graphics mode

MBOOT_MAGIC         equ 0x1BADB002                                          ; Multiboot magic value, lets the bootloader find the multboot header
MBOOT_FLAGS         equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO | MBOOT_GRAPHICS  ; We set the multboot flags so grub knows what modules we will use
MBOOT_CHECKSUM      equ -(MBOOT_MAGIC + MBOOT_FLAGS)                        ; Check everything was set up properly

STACK_SIKE          equ 2*1024*1024                                         ; Set the stack size to 2 MiB

; Write the multiboot header data so grub can load us
section .multiboot
    align 4
    dd MBOOT_MAGIC
    dd MBOOT_FLAGS
    dd MBOOT_CHECKSUM

BITS 32                                                                    ; We are using 32 code
; Set up the start function (Wich is our entry point)
section .text
    extern kernel_early
    extern _init
    extern kernel_main

global start:function (start.end - start)                                   ; Started is declared as a function symbol with its size size=start.end - start.beggining
start:
    mov esp, stack_top                                                      ; Set the stack pointer to the top of our stack
    mov ebp, 0                                                              ; Set a landing point for stack traces
    cli                                                                     ; Disable interrupts

    call kernel_early                                                       ; Init the core kernel code
    call _init                                                              ; Call global constructors
    
    push ebx                                                                ; Push the multiboot header location
    push esp                                                                ; Pass the stack address
    call kernel_main                                                        ; Call kernel main

.hang:                                                                      ; Loop forever
    hlt
    jmp .hang

.end:                                                                      ; Set the start.end to the end of the start function


; Set up the stack (has to be 16KiB aligned) and the stack_bottom and stack_top symbols
section .bootstrap_stack nobits
    align 16
    stack_bottom:
        resb STACK_SIKE
    stack_top: