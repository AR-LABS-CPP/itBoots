#pragma once

#include "types.h"

#define KBD_DATA_PORT   0x60

void initKeyboard(void);
void keyboardHandler(void);
uint8_t readScanCode(void);
void translateScanCodeToASCII(uint8_t scanCode);