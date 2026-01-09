#include "../include/framebuffer.h"
#include "../include/io.h"

/*
    Check resources for x86_MEMORY_MAP_REAL_MODE

    A.R.
*/

#define VIDEO_ADDRESS 0xB8000
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5
#define FB_HIGH_BYTE_CMD 14
#define FB_LOW_BYTE_CMD 15

static volatile char *videoMemory = (volatile char *)VIDEO_ADDRESS;
static uint16_t cursorPos = 0;
static unsigned char fgColor = COLOR_LIGHT_GRAY;
static unsigned char bgColor = COLOR_BLACK;

static void framebufferWriteCell(uint16_t pos, char c, unsigned char fg, unsigned char bg) {
    uint16_t offset = pos * 2;
    videoMemory[offset] = c;
    videoMemory[offset + 1] = ((bg & 0x0F) << 4) | (fg & 0x0F);
}

static void framebufferUpdateCursor(void) {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_CMD);
    outb(FB_DATA_PORT, (cursorPos >> 8) & 0xFF);
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_CMD);
    outb(FB_DATA_PORT, cursorPos & 0xFF);
}

static void scroll(void) {
    uint16_t idx;

    /* Copy each line up */
    for (idx = 0; idx < (FRAMEBUFFER_HEIGHT - 1) * FRAMEBUFFER_WIDTH * 2; idx++) {
        videoMemory[idx] = videoMemory[idx + FRAMEBUFFER_WIDTH * 2];
    }

    /* Clear the last line */
    for (idx = (FRAMEBUFFER_HEIGHT - 1) * FRAMEBUFFER_WIDTH;
         idx < FRAMEBUFFER_HEIGHT * FRAMEBUFFER_WIDTH; idx++) {
        framebufferWriteCell(idx, ' ', fgColor, bgColor);
    }
}

void framebufferInit(void) {
    framebufferClear();
}

void framebufferClear(void) {
    uint16_t idx;
    
    for (idx = 0; idx < FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT; idx++) {
        framebufferWriteCell(idx, ' ', fgColor, bgColor);
    }
    
    cursorPos = 0;
    framebufferUpdateCursor();
}

void framebufferWrite(const char *str) {
    uint32_t idx = 0;

    while (str[idx] != '\0') {
        char c = str[idx];

        if (c == '\n') {
            cursorPos = ((cursorPos / FRAMEBUFFER_WIDTH) + 1) * FRAMEBUFFER_WIDTH;
        }
        else if (c == '\r') {
            cursorPos = (cursorPos / FRAMEBUFFER_WIDTH) * FRAMEBUFFER_WIDTH;
        }
        else if (c == '\b') {
            if (cursorPos > 0) {
                cursorPos--;
                framebufferWriteCell(cursorPos, ' ', fgColor, bgColor);
            }
        }
        else if (c == '\t') {
            cursorPos += 4;
            cursorPos -= cursorPos % 4;
        }
        else {
            framebufferWriteCell(cursorPos, c, fgColor, bgColor);
            cursorPos++;
        }

        if (cursorPos >= FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT) {
            scroll();
            cursorPos = (FRAMEBUFFER_HEIGHT - 1) * FRAMEBUFFER_WIDTH;
        }

        idx++;
    }

    framebufferUpdateCursor();
}

void framebufferSetColors(unsigned char fg, unsigned char bg) {
    fgColor = fg;
    bgColor = bg;
}

void framebufferMoveCursor(uint16_t row, uint16_t col) {
    if (row < FRAMEBUFFER_HEIGHT && col < FRAMEBUFFER_WIDTH) {
        cursorPos = row * FRAMEBUFFER_WIDTH + col;
        framebufferUpdateCursor();
    }
}