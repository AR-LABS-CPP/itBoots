#include "../include/framebuffer.h"
#include "../include/gdt.h"
#include "../include/idt.h"
#include "../include/pic.h"
#include "../include/keyboard.h"
#include "../include/types.h"

void kMain(void) {    
    framebufferInit();
    framebufferSetColors(COLOR_WHITE, COLOR_BLACK);
    
    const char* welcome = "========= TWITTY TWO V0.1 =========\n";
    framebufferWrite(welcome);
    
    initGDT();
    initIDT();
    initPic();
    initKeyboard();
    
    framebufferWrite("\n>> ");

    /* Hang indefinitely - interrupts will handle keyboard */
    for (;;) {
        __asm__ volatile("hlt");
    }
}