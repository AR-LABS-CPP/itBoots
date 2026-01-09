#pragma once

#define SERIAL_COM1_BASE                    0x3F8

#define SERIAL_PORT_DATA(base)              (base)
#define SERIAL_PORT_FIFO_COMMAND(base)      (base + 2)
#define SERIAL_PORT_LINE_COMMAND(base)      (base + 3)
#define SERIAL_PORT_MODEM_COMMAND(base)     (base + 4)
#define SERIAL_PORT_LINE_STATUS(base)       (base + 5)

#define SERIAL_LINE_ENABLE_DLAB             0x80

/* I just added them here for no reason, looking fancy, no? */
#define BAUD_RATE_50        0x0900
#define BAUD_RATE_110       0x0417
#define BAUD_RATE_220       0x020C
#define BAUD_RATE_300       0x0180
#define BAUD_RATE_600       0x00C0
#define BAUD_RATE_1200      0x0060
#define BAUD_RATE_2400      0x0030
#define BAUD_RATE_4800      0x0018
#define BAUD_RATE_9600      0x000C
#define BAUD_RATE_19200     0x0006
#define BAUD_RATE_38400     0x0003
#define BAUD_RATE_57600     0x0002
#define BAUD_RATE_115200    0x0001

void serialConfigureBaudRate(unsigned short com, unsigned short div);
void serialConfigureLine(unsigned short com);
void serialConfigureBuffer(unsigned short com);
void serialConfigureModem(unsigned short com);
int serialIsTransmitFifoEmpty(unsigned int com);

void serialWrite(unsigned short com, unsigned char byte);
void serialWriteString(unsigned short com, unsigned char* str);