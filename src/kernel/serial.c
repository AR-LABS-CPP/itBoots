#include "../include/serial.h"
#include "../include/io.h"

/*
    Senor please read here to understand these magic values
    https://caro.su/msx/ocm_de1/16550.pdf

    A.R.
*/

void serialConfigureBaudRate(
    unsigned short com,
    unsigned short div
) {
    outb(
        SERIAL_PORT_LINE_COMMAND(com),
        SERIAL_LINE_ENABLE_DLAB
    );
    outb(
        SERIAL_PORT_DATA(com),
        (div >> 8) & 0x00FF
    );
    outb(SERIAL_PORT_DATA(com), div & 0x00FF);
}

void serialConfigureLine(unsigned short com) {
    /*
        Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
        Content: | d | b | prty  | s | dl  |
        Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
    */
    outb(SERIAL_PORT_LINE_COMMAND(com), 0x03);
}

void serialConfigureBuffer(unsigned short com) {
    /*
        Bit:     | 7 6 | 5 | 4 | 3 | 2 | 1 | 0 |
        Content: | lvl |bs | r |dma|clt|clr| e |
        Value:   | 11  | 0 | 0 | 0 | 1 | 1 | 1 | = 0xC7
    */
    outb(SERIAL_PORT_FIFO_COMMAND(com), 0xC7);
}

void serialConfigureModem(unsigned short com) {
    /*
        Bit:     | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
        Content: | r | r |af |lb |ao2|ao1|rts|dtr|
        Value:   | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 | = 0x03
    */
    outb(SERIAL_PORT_MODEM_COMMAND(com), 0x03);
}

int serialIsTransmitFifoEmpty(unsigned int com) {
    /*
        If bit 5 of the line status register is set then
        transmit buffer is empty.

        0x20 = 0b00100000
    */
    return inb(SERIAL_PORT_LINE_STATUS(com)) & 0x20;
}

void serialWrite(unsigned short com, unsigned char byte) {
    while(!serialIsTransmitFifoEmpty(com)) {}
    outb(SERIAL_PORT_DATA(com), byte);
}

void serialWriteString(unsigned short com, unsigned char* str) {
    while(*str != '\0') {
        serialWrite(com, *str);
        str++;
    }
}