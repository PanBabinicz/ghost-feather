MEMORY
{
    rom_bootloader (rx)  : ORIGIN = 0x00200000, LENGTH = 0x00004000
    rom_apploader  (rx)  : ORIGIN = 0x00204000, LENGTH = 0x00004000
    rom_updater    (rx)  : ORIGIN = 0x00208000, LENGTH = 0x00008000
    rom_app        (rx)  : ORIGIN = 0x00210000, LENGTH = 0x00008000
    sram_bootloader(rwx) : ORIGIN = 0x20010000, LENGTH = 0x00004000
    sram_apploader (rwx) : ORIGIN = 0x20014000, LENGTH = 0x00002000
    sram_updater   (rwx) : ORIGIN = 0x20016000, LENGTH = 0x00008000
    sram_app       (rwx) : ORIGIN = 0x2001e000, LENGTH = 0x0001dfff
}

__bootloader_start__ = ORIGIN(rom_bootloader);
__bootloader_size__  = LENGTH(rom_bootloader);
__apploader_start__  = ORIGIN(rom_apploader);
__apploader_size__   = LENGTH(rom_apploader);
__updater_start__    = ORIGIN(rom_updater);
__updater_size__     = LENGTH(rom_updater);
__app_start__        = ORIGIN(rom_app);
__app_size__         = LENGTH(rom_app);
