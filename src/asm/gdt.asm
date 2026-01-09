bits 32

global gdtFlush

gdtFlush:
    mov eax, [esp + 4]          ; pointer to gdtPtr
    lgdt [eax]

    mov ax, 0x10                ; kernel data selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp 0x08:.flush             ; reload CS
.flush:
    ret
