bits 32

global idtFlush

idtFlush:
    mov eax, [esp + 4]          ; pointer to idtPtr
    lidt [eax]
    ret
