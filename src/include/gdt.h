#pragma once

#include "types.h"

#define NULL_SELECTOR   0x00
#define CS_KERNEL       0x08
#define DS_KERNEL       0x10
#define CS_USER         0x18
#define DS_USER         0x20

#define GDT_NUM_ENTRIES 5

typedef struct {
    uint16_t limitLow;      
    uint16_t baseLow;
    uint8_t  baseMiddle;
    uint8_t  access;        
    uint8_t  granularity;
    uint8_t  baseHigh;
} __attribute__((packed)) gdtEntry_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gdtPtr_t;

extern void gdtFlush(uint32_t);
void initGDT(void);