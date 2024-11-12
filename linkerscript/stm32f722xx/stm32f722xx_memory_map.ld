MEMORY
{
    bootrom1   (rx)  : ORIGIN = 0x00200000, LENGTH = 0x00004000
    bootrom2   (rx)  : ORIGIN = 0x00204000, LENGTH = 0x00004000
    approm     (rx)  : ORIGIN = 0x08008000, LENGTH = 0x00008000
    sram_boot1 (rwx) : ORIGIN = 0x20010000, LENGTH = 0x00010000
    sram_boot2 (rwx) : ORIGIN = 0x20020000, LENGTH = 0x00010000
    sram_app   (rwx) : ORIGIN = 0x20030000, LENGTH = 0x0001bfff
}

__bootrom1_start__ = ORIGIN(bootrom1);
__bootrom1_size__  = LENGTH(bootrom1);
__bootrom2_start__ = ORIGIN(bootrom2);
__bootrom2_size__  = LENGTH(bootrom2);
__approm_start__   = ORIGIN(approm);
__approm_size__    = LENGTH(approm);
