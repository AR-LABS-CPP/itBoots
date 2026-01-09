#include "../include/pic.h"
#include "../include/io.h"

#define PIC1_COMMAND    0x20
#define PIC1_DATA       0x21
#define PIC2_COMMAND    0xA0
#define PIC2_DATA       0xA1

#define ICW1_ICW4       0x01
#define ICW1_INIT       0x10
#define ICW4_8086       0x01

/*
    Don't ask me how I got here.
    I am just trying to survive man.

    A.R.
*/
void initPic(void) {
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC1_DATA, PIC1_START_INTERRUPT);
    outb(PIC2_DATA, PIC2_START_INTERRUPT);
    outb(PIC1_DATA, 0x04);
    outb(PIC2_DATA, 0x02);
    outb(PIC1_DATA, ICW4_8086);
    outb(PIC2_DATA, ICW4_8086);
    outb(PIC1_DATA, 0xFD);  /* 11111101 - only IRQ1 unmasked */
    outb(PIC2_DATA, 0xFF);  /* 11111111 - all masked */
}

void picAcknowledge(uint32_t interrupt) {
    if(
        interrupt < PIC1_START_INTERRUPT ||
        interrupt > PIC2_END_INTERRUPT
    ) {
        return;
    }

    if(interrupt >= PIC2_START_INTERRUPT) {
        outb(PIC2_COMMAND, PIC_ACK);
    }
    outb(PIC1_COMMAND, PIC_ACK);
}