OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)
SECTIONS
{
    . = 0x100000;
    .text : ALIGN(4K)
    {
        *(.text)
        *(.text.*)
    } :text
    
    .rodata : ALIGN(4K)
    {
        *(.rodata)
        *(.rodata.*)
    } :rodata
    
    .data : ALIGN(4K)
    {
        *(.data)
        *(.data.*)
        *(.got.plt)
    } :data
    
    .bss : ALIGN(4K)
    {
        *(.bss)
        *(COMMON)
    } :bss
}

/*
    R = read
    W = write
    E = execute
*/

PHDRS
{
    text   PT_LOAD FLAGS(5); /* RE */
    rodata PT_LOAD FLAGS(4); /* R */
    data   PT_LOAD FLAGS(6); /* RW */
    bss    PT_LOAD FLAGS(6); /* RW */
}