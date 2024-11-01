MEMORY
{
    bootrom (rx)  : ORIGIN = 0x02000000, LENGTH = 0x00002000
    approm  (rx)  : ORIGIN = 0x08000000, LENGTH = 0x00008000
    sram1   (rwx) : ORIGIN = 0x20010000, LENGTH = 0x0003bfff
}

__bootrom_start__ = ORIGIN(bootrom);
__bootrom_size__  = LENGTH(bootrom);
__approm_start__  = ORIGIN(approm);
__approm_size__   = LENGTH(approm);
