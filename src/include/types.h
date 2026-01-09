#pragma once

typedef unsigned char           uint8_t;
typedef unsigned short          uint16_t;
typedef unsigned int            uint32_t;
typedef unsigned long long      uint64_t;

typedef signed char             int8_t;
typedef signed short            int16_t;
typedef signed int              int32_t;
typedef signed long long        int64_t;

typedef uint32_t                size_t;

/* Poor man's NULL */
#define NULL ((void*)0)

#define COLOR_BLACK             0x0
#define COLOR_BLUE              0x1
#define COLOR_GREEN             0x2
#define COLOR_CYAN              0x3
#define COLOR_RED               0x4
#define COLOR_MAGENTA           0x5
#define COLOR_BROWN             0x6
#define COLOR_LIGHT_GRAY        0x7
#define COLOR_DARK_GRAY         0x8
#define COLOR_LIGHT_BLUE        0x9
#define COLOR_LIGHT_GREEN       0xA
#define COLOR_LIGHT_CYAN        0xB
#define COLOR_LIGHT_RED         0xC
#define COLOR_LIGHT_MAGENTA     0xD
#define COLOR_LIGHT_BROWN       0xE
#define COLOR_WHITE             0xF