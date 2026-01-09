#pragma once

#include "types.h"

#define PIC1_PORT_A             0x20
#define PIC2_PORT_A             0xA0

#define PIC1_START_INTERRUPT    0x20
#define PIC2_START_INTERRUPT    0x28
#define PIC2_END_INTERRUPT      PIC2_START_INTERRUPT + 7

#define PIC_ACK                 0x20

void initPic(void);
void picAcknowledge(uint32_t interrupt);