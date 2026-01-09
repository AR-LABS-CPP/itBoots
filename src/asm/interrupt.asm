bits 32

; ===================================================
; For the poor souls who think I wrote this ASM all by
; myself, think again.

; Gugu gaga gugu. Buhahahahahahahahaha
; ===================================================

extern interrupt_handler    ; C handler

%macro ISR_NOERR 1
global interrupt_handler_%1
interrupt_handler_%1:
    cli
    push dword 0            ; there is no error code, so 0ro it is
    push dword %1
    jmp common_interrupt_handler
%endmacro

%macro ISR_ERR 1
global interrupt_handler_%1
interrupt_handler_%1:
    cli
    push dword %1
    jmp common_interrupt_handler
%endmacro

common_interrupt_handler:
    pushad

    push ds
    push es
    push fs
    push gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp
    call interrupt_handler
    add esp, 4

    pop gs
    pop fs
    pop es
    pop ds

    popad

    add esp, 8
    sti
    iret

ISR_NOERR 0      ; #DE Divide Error
ISR_NOERR 1      ; #DB Debug
ISR_NOERR 2      ; NMI
ISR_NOERR 3      ; Breakpoint
ISR_NOERR 4      ; Overflow
ISR_NOERR 5      ; Bound Range
ISR_NOERR 6      ; Invalid Opcode
ISR_ERR   8      ; Double Fault
ISR_NOERR 9
ISR_ERR   10     ; Invalid TSS
ISR_ERR   11     ; Segment Not Present
ISR_ERR   12     ; Stack Fault
ISR_ERR   13     ; General Protection
ISR_ERR   14     ; Page Fault
ISR_NOERR 15
ISR_ERR   17     ; Alignment Check

; Hardware IRQs (PIC remapped 32–47)
%assign i 32
%rep 16
    ISR_NOERR i
%assign i i+1
%endrep

; Software interrupts (48–255)
%assign i 48
%rep 208
    ISR_NOERR i
%assign i i+1
%endrep