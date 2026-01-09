bits 32

global outb
global inb

outb:
    mov dx, [esp + 4]           ; this is port
    mov al, [esp + 8]           ; and this is data
    out dx, al
    ret

inb:
    mov dx, [esp + 4]           ; Hi, port here again
    in al, dx
    ret
