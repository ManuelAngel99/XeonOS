;
; Author: Manuel Ángel Suárez Álvarez
; E-mail Manuel_Angel99@outlook.com
; Created: 2016-08-13 20:54:25
; 
; File: interrupt_stubs.asm
; Description: Defines the interrupt stubs
;

section .text

extern exception_handler 				; interrupt_handler is defined elsewhere
extern irq_handler                      ; irq handler is defined elsewhere

global common_interrupt_handler
common_interrupt_handler:				; All the interrupt handlers will have this in common
    pusha                               ; Pushes EDI, ESI, EBP, ESP, EBX, EDX, ECX and EAX

    mov ax, ds                          ; Set AX to the current data segment descriptor
    push eax                            ; Save the data segment descriptor on the stack

    mov ax, 0x10                        ; Give the CPU the kernel’s clean data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call exception_handler
    hlt

    pop eax                             ; Get the orginal data segment descriptor back
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa                                ; Pops EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX
    add esp, 8                          ; Get rid of the pushed error code and interrupt vector
    sti                                 ; Re-enable interrupts
    iret                                ; Tidy up the stack, ready for the next interrupt


global common_irq_handler
common_irq_handler:
    pusha                   ; Pushes EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX

    mov ax, ds              ; Set AX to the current data segment descriptor
    push eax                ; Save the data segment descriptor on the stack
    
    mov ax, 0x10            ; Give the CPU the kernel’s clean data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call irq_handler

    pop eax                 ; Get the original data segment descriptor back
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa                    ; Pops EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX
    add esp, 8              ; Get rid of the pushed error code and interrupt vector
    sti                     ; Re-enable interrupts
    iret                    ; Tidy up the stack, ready for the next interrupt


; --------------------------------> INTERRUPT AND IRQ MACROS <---------------------------------------------


%macro error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
    cli                                 ; Clear interrupts
    push    dword %1                    ; Push the interrupt number
    jmp     common_interrupt_handler    ; Jump to the generic handler
%endmacro


%macro no_error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
   push    dword 0                     ; push 0 as error code
   push    dword %1                    ; push the interrupt number
   jmp     common_interrupt_handler    ; jump to the common handler
%endmacro

%macro irq 1
global irq_handler_%1:
irq_handler_%1:
    cli                                 ; clears interrupts
    push dword 0                        ;
    push dword %1                       ;
    jmp  common_irq_handler
%endmacro


; ---------------------------------> MACRO CALLS <-------------------------------------------

; Some CPU exceptions have error codes, some don't

%assign intnum 0
%rep 8 - intnum
    no_error_code_interrupt_handler intnum
    %assign intnum intnum + 1
%endrep

error_code_interrupt_handler 8
no_error_code_interrupt_handler 9

%assign intnum 10
%rep 16 - intnum
    error_code_interrupt_handler intnum
    %assign intnum intnum + 1
%endrep

no_error_code_interrupt_handler 16
error_code_interrupt_handler 17
no_error_code_interrupt_handler 18
no_error_code_interrupt_handler 19
no_error_code_interrupt_handler 20

%assign intnum 21   ; first (currently) unassigned CPU exception
%rep 32 - intnum
    no_error_code_interrupt_handler intnum
    %assign intnum intnum + 1
%endrep

%assign intnum 32   ; irq interrupts
%rep 255 - intnum
    irq intnum
    %assign intnum intnum + 1
%endrep



;
; -------------> Define a table of interrupt handlers for C code to use <---------------
;

global interrupt_handler_table
interrupt_handler_table:

%assign intnum 0
%rep 32
    dd  interrupt_handler_ %+ intnum    ; Write the interrupt_handler_X address to the binary
    %assign intnum intnum + 1
%endrep
%rep 255 - intnum
    dd irq_handler_%+ intnum            ; Write the irq_handler_X address to the binart
    %assign intnum intnum + 1
%endrep