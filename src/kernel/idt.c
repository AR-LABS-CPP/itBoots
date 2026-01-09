#include "../include/idt.h"
#include "../include/pic.h"
#include "../include/keyboard.h"

static idtEntry_t idtEntries[256];

typedef struct {
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} __attribute__((packed)) registers_t;

/*
    NOTE_TO_SELF: mama mia

    A.R.
*/
extern void interrupt_handler_0(void);
extern void interrupt_handler_1(void);
extern void interrupt_handler_2(void);
extern void interrupt_handler_3(void);
extern void interrupt_handler_4(void);
extern void interrupt_handler_5(void);
extern void interrupt_handler_6(void);
extern void interrupt_handler_8(void);
extern void interrupt_handler_9(void);
extern void interrupt_handler_10(void);
extern void interrupt_handler_11(void);
extern void interrupt_handler_12(void);
extern void interrupt_handler_13(void);
extern void interrupt_handler_14(void);
extern void interrupt_handler_15(void);
extern void interrupt_handler_17(void);
extern void interrupt_handler_32(void);
extern void interrupt_handler_33(void);
extern void interrupt_handler_34(void);
extern void interrupt_handler_35(void);
extern void interrupt_handler_36(void);
extern void interrupt_handler_37(void);
extern void interrupt_handler_38(void);
extern void interrupt_handler_39(void);
extern void interrupt_handler_40(void);
extern void interrupt_handler_41(void);
extern void interrupt_handler_42(void);
extern void interrupt_handler_43(void);
extern void interrupt_handler_44(void);
extern void interrupt_handler_45(void);
extern void interrupt_handler_46(void);
extern void interrupt_handler_47(void);

static void* isr_handlers[48] = {
    interrupt_handler_0, interrupt_handler_1, interrupt_handler_2, interrupt_handler_3,
    interrupt_handler_4, interrupt_handler_5, interrupt_handler_6, 0,
    interrupt_handler_8, interrupt_handler_9, interrupt_handler_10, interrupt_handler_11,
    interrupt_handler_12, interrupt_handler_13, interrupt_handler_14, interrupt_handler_15,
    0, interrupt_handler_17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    interrupt_handler_32, interrupt_handler_33, interrupt_handler_34, interrupt_handler_35,
    interrupt_handler_36, interrupt_handler_37, interrupt_handler_38, interrupt_handler_39,
    interrupt_handler_40, interrupt_handler_41, interrupt_handler_42, interrupt_handler_43,
    interrupt_handler_44, interrupt_handler_45, interrupt_handler_46, interrupt_handler_47
};

void setIDTEntry(uint8_t vector, void* handler, uint8_t dpl) {
    if (!handler) return;
    
    uint32_t addr = (uint32_t)handler;
    idtEntry_t* entry = &idtEntries[vector];

    entry->offsetLow = addr & 0xFFFF;
    entry->selector = 0x08;  /* CS */
    entry->zero = 0;
    entry->flags = 0x8E | ((dpl & 0x3) << 5);
    entry->offsetHigh = (addr >> 16) & 0xFFFF;
}

void initIDT(void) {
    for (int i = 0; i < 48; i++) {
        if (isr_handlers[i]) {
            setIDTEntry(i, isr_handlers[i], 0);
        }
    }
    
    loadIDT();
}

void loadIDT(void) {
    idtPtr_t idtReg;
    idtReg.limit = sizeof(idtEntries) - 1;
    idtReg.base  = (uint32_t)&idtEntries;
    idtFlush((uint32_t)&idtReg);
}

void interrupt_handler(registers_t* regs) {
    if (regs->int_no >= 32 && regs->int_no < 48) {
        /* Keyboard interrupt (IRQ1 = interrupt 33) */
        if (regs->int_no == 33) {
            keyboardHandler();
        }
        
        picAcknowledge(regs->int_no);
    }
    else if (regs->int_no < 32) {
        /* For now, just hang on CPU exceptions */
        for(;;);
    }
}
