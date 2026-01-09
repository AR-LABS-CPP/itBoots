#include "../include/gdt.h"

static gdtEntry_t gdtEntries[GDT_NUM_ENTRIES];
static gdtPtr_t gdtPtr;

static void gdtSetGate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdtEntries[num].baseLow = (base & 0xFFFF);
    gdtEntries[num].baseMiddle = (base >> 16) & 0xFF;
    gdtEntries[num].baseHigh = (base >> 24) & 0xFF;

    gdtEntries[num].limitLow = (limit & 0xFFFF);
    gdtEntries[num].granularity = (limit >> 16) & 0x0F;

    gdtEntries[num].granularity |= gran & 0xF0;
    gdtEntries[num].access = access;
}

/*
    Long read: https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-vol-3a-part-1-manual.pdf,
    specifically from section 3.4.5.1

    short read: GYPTEEEEEEEEE

    A.R.
*/
void initGDT(void) {
    gdtPtr.limit = (sizeof(gdtEntry_t) * GDT_NUM_ENTRIES) - 1;
    gdtPtr.base = (uint32_t)&gdtEntries;

    gdtSetGate(0, 0, 0, 0, 0); /* NULL descriptor */
    gdtSetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdtSetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    gdtSetGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    gdtSetGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    gdtFlush((uint32_t)&gdtPtr);
}