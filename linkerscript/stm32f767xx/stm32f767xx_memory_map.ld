MEMORY
{
    bootrom (rx)  : ORIGIN = 0x08000000, LENGTH = 0x00004000
    approm  (rx)  : ORIGIN = 0x08004000, LENGTH = 0x001fbfff
    ram     (rwx) : ORIGIN = 0x20020000, LENGTH = 0x0007bfff
}

__bootrom_start__ = ORIGIN(bootrom);
__bootrom_size__  = LENGTH(bootrom);
__approm_start__  = ORIGIN(approm);
__approm_size__   = LENGTH(approm);
