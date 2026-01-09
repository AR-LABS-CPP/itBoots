#pragma once

#include "types.h"

typedef struct {
    uint16_t offsetLow;
    uint16_t selector;
    uint8_t  zero;
    uint8_t  flags;
    uint16_t offsetHigh;
} __attribute__((packed)) idtEntry_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idtPtr_t;

extern void idtFlush(uint32_t);

void initIDT(void);
void setIDTEntry(uint8_t vector, void* handler, uint8_t dpl);
void loadIDT(void);