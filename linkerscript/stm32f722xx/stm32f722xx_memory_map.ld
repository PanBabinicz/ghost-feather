MEMORY
{
    bootrom1   (rx)  : ORIGIN = 0x00200000, LENGTH = 0x00004000
    bootrom2   (rx)  : ORIGIN = 0x00204000, LENGTH = 0x00004000
    ubootrom   (rx)  : ORIGIN = 0x00208000, LENGTH = 0x0000c000
    approm     (rx)  : ORIGIN = 0x08014000, LENGTH = 0x00008000
    sram_boot1 (rwx) : ORIGIN = 0x20010000, LENGTH = 0x00002000
    sram_boot2 (rwx) : ORIGIN = 0x20012000, LENGTH = 0x00002000
    sram_uboot (rwx) : ORIGIN = 0x20014000, LENGTH = 0x00004000
    sram_app   (rwx) : ORIGIN = 0x20018000, LENGTH = 0x00023fff
}

__bootrom1_start__ = ORIGIN(bootrom1);
__bootrom1_size__  = LENGTH(bootrom1);
__bootrom2_start__ = ORIGIN(bootrom2);
__bootrom2_size__  = LENGTH(bootrom2);
__ubootrom_start__ = ORIGIN(ubootrom);
__ubootrom_size__  = LENGTH(ubootrom);
__approm_start__   = ORIGIN(approm);
__approm_size__    = LENGTH(approm);
