# Memory layout

> [!NOTE]
> ```
> MEMORY
> {
>     bootrom1   (rx)  : ORIGIN = 0x00200000, LENGTH = 0x00004000
>     bootrom2   (rx)  : ORIGIN = 0x00204000, LENGTH = 0x00004000
>     approm     (rx)  : ORIGIN = 0x08008000, LENGTH = 0x00008000
>     sram_boot1 (rwx) : ORIGIN = 0x20010000, LENGTH = 0x00010000
>     sram_boot2 (rwx) : ORIGIN = 0x20020000, LENGTH = 0x00010000
>     sram_app   (rwx) : ORIGIN = 0x20030000, LENGTH = 0x0001bfff
> }
> ```
>
> The ITCM and AXI interfaces use the same physical flash memory. The information
> about flash memory organization can be found in the reference manual, chapter 3
> Embedded Flash memory, Table 3.
>
> That is why approm starts on the address 0x08080000. The first 32kB are occupied by
> the first and second bootloaders.