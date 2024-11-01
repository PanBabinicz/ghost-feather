INCLUDE stm32f767_memory_map.ld

STACK_SIZE = DEFINED(STACK_SIZE) ? STACK_SIZE : DEFINED(__stack_size__) ? __stack_size__ : 0x2000;

SECTIONS
{
    .text :
    {
        . = ALIGN(4);
        _stext = .;
        KEEP(*(.vector_table))
        *(.text)
        *(.rodata)
        . = ALIGN(4);
        _etext = .;
    } > bootrom

    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        *(COMMON)
        . = ALIGN(4)
        _ebss = .;
    } > ram

    .data :
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        . = ALIGN(4);
        _edata = .;
    } > ram AT > bootrom

    .stack (NOLOAD) :
    {
        . = ALIGN(8);
        _sstack = .;
        . = . + STACK_SIZE;
        . = ALIGN(8);
        _estack = .;
    } > ram

    . = ALIGN(4);
    _end = .;
}
