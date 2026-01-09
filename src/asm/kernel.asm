bits 32

section .note.GNU-stack

; Don't ask me how I got here
; I am just trying to survive man
section .text
    align 4                     ; multiboot spec
    dd 0x1BADB002
    dd 0x00
    dd -(0x1BADB002 + 0x00)     ; checksum

global _start
extern kMain

_start:
    sti                         ; set interrupt flag
    mov esp, stack_space        ; set stack pointer
    call kMain
hang:
    hlt                         ; confuse the CPU by halting
    jmp hang                    ; loop forever

section .bss
align 4
stack_space:
    resb 8192                   ; 8KB for stack