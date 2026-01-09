#include "../include/keyboard.h"
#include "../include/io.h"
#include "../include/framebuffer.h"
#include "../include/pic.h"

/* Simple US keyboard layout - scancode to ASCII mapping */
static const char scancode_to_ascii[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, /* Ctrl */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, /* Left shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
    0, /* Right shift */
    '*',
    0, /* Alt */
    ' ' /* Space */
};

void initKeyboard(void) {}

uint8_t readScanCode(void) {
    return inb(KBD_DATA_PORT);
}

void translateScanCodeToASCII(uint8_t scanCode) {
    /* Only handle key press (release has bit 7 set) */
    if (scanCode & 0x80) {
        return;
    }
    
    if (scanCode < sizeof(scancode_to_ascii)) {
        char c = scancode_to_ascii[scanCode];
        if (c != 0) {
            char str[2] = {c, '\0'};
            framebufferWrite(str);
        }
    }
}

void keyboardHandler(void) {
    uint8_t scancode = readScanCode();
    translateScanCodeToASCII(scancode);
}