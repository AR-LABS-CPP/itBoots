#pragma once

#include "types.h"

#define FRAMEBUFFER_WIDTH   80
#define FRAMEBUFFER_HEIGHT  25

void framebufferInit(void);
void framebufferClear(void);
void framebufferWrite(const char* str);
void framebufferSetColors(unsigned char fg, unsigned char bg);
void framebufferMoveCursor(uint16_t row, uint16_t col);