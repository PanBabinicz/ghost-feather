        .syntax unified
        .cpu cortex-m4
        .thumb

        .macro defisr name
            .global \name
            .weak \name
            .type \name, %function
            .thumb_set \name, _default_handler
            .word \name
        .endm

        .section ._vector_table, "a"
        .balign 4
        .global _vector_table
        .type _vector_table, %object
_vector_table:                                  @ |-   Offset   -|
        .word _stack_end                        @ |- 0x00000000 -| 
        defisr _reset_handler                   @ |- 0x00000004 -|
        defisr _nmi_handler                     @ |- 0x00000008 -|
        defisr _hardfault_handler               @ |- 0x0000000c -|
        defisr _memmanage_handler               @ |- 0x00000010 -|
        defisr _busfault_handler                @ |- 0x00000014 -|
        defisr _usagefault_handler              @ |- 0x00000018 -|
        .word 0                                 @ |- 0x0000001c -|
        .word 0                                 @ |- 0x00000020 -|
        .word 0                                 @ |- 0x00000024 -|
        .word 0                                 @ |- 0x00000028 -|
        defisr _svcall_handler                  @ |- 0x0000002c -|
        defisr _debugmonitor_handler            @ |- 0x00000030 -|
        .word 0                                 @ |- 0x00000034 -|
        defisr _pendsv_handler                  @ |- 0x00000038 -|
        defisr _systick_handler                 @ |- 0x0000003c -|
        defisr _wwdg_handler                    @ |- 0x00000040 -|
        defisr _pvd_handler                     @ |- 0x00000044 -|
        defisr _tampstamp_handler               @ |- 0x00000048 -|
        defisr _rtcwkup_handler                 @ |- 0x0000004c -|
        defisr _flash_handler                   @ |- 0x00000050 -|
        defisr _rcc_handler                     @ |- 0x00000054 -|
        defisr _exti0_handler                   @ |- 0x00000058 -|
        defisr _exti1_handler                   @ |- 0x0000005c -|
        defisr _exti2_handler                   @ |- 0x00000060 -|
        defisr _exti3_handler                   @ |- 0x00000064 -|
        defisr _exti4_handler                   @ |- 0x00000068 -|
        defisr _dma1stream0_handler             @ |- 0x0000006c -|
        defisr _dma1stream1_handler             @ |- 0x00000070 -|
        defisr _dma1stream2_handler             @ |- 0x00000074 -|
        defisr _dma1stream3_handler             @ |- 0x00000078 -|
        defisr _dma1stream4_handler             @ |- 0x0000007c -|
        defisr _dma1stream5_handler             @ |- 0x00000080 -|
        defisr _dma1stream6_handler             @ |- 0x00000084 -|
        defisr _adc_handler                     @ |- 0x00000088 -|
        defisr _can1tx_handler                  @ |- 0x0000008c -|
        defisr _can1rx0_handler                 @ |- 0x00000090 -|
        defisr _can1rx1_handler                 @ |- 0x00000094 -|
        defisr _can1sce_handler                 @ |- 0x00000098 -|
        defisr _exti95_handler                  @ |- 0x0000009c -|
        defisr _tim1brktim9_handler             @ |- 0x000000a0 -|
        defisr _tim1uptim10_handler             @ |- 0x000000a4 -|
        defisr _tim1trgcomtim11_handler         @ |- 0x000000a8 -|
        defisr _tim1cc_handler                  @ |- 0x000000ac -|
        defisr _tim2_handler                    @ |- 0x000000b0 -|
        defisr _tim3_handler                    @ |- 0x000000b4 -|
        defisr _tim4_handler                    @ |- 0x000000b8 -|
        defisr _i2c1ev_handler                  @ |- 0x000000bc -|
        defisr _i2c1er_handler                  @ |- 0x000000c0 -|
        defisr _i2c2ev_handler                  @ |- 0x000000c4 -|
        defisr _i2c2er_handler                  @ |- 0x000000c8 -|
        defisr _spi1_handler                    @ |- 0x000000cc -|
        defisr _spi2_handler                    @ |- 0x000000d0 -|
        defisr _usart1_handler                  @ |- 0x000000d4 -|
        defisr _usart2_handler                  @ |- 0x000000d8 -|
        defisr _usart3_handler                  @ |- 0x000000dc -|
        defisr _exti1510_handler                @ |- 0x000000e0 -|
        defisr _rtcalarm_handler                @ |- 0x000000e4 -|
        defisr _otgfswkup_handler               @ |- 0x000000e8 -|
        defisr _tim8brktim12_handler            @ |- 0x000000ec -|
        defisr _tim8uptim13_handler             @ |- 0x000000f0 -|
        defisr _tim8trgcomtim14_handler         @ |- 0x000000f4 -|
        defisr _tim8cc_handler                  @ |- 0x000000f8 -|
        defisr _dma1stream7_handler             @ |- 0x000000fc -|
        defisr _fmc_handler                     @ |- 0x00000100 -|
        defisr _sdio_handler                    @ |- 0x00000104 -|
        defisr _tim5_handler                    @ |- 0x00000108 -|
        defisr _spi3_handler                    @ |- 0x0000010c -|
        defisr _uart4_handler                   @ |- 0x00000110 -|
        defisr _uart5_handler                   @ |- 0x00000114 -|
        defisr _tim6dac_handler                 @ |- 0x00000118 -|
        defisr _tim7_handler                    @ |- 0x0000011c -|
        defisr _dma2stream0_handler             @ |- 0x00000120 -|
        defisr _dma2stream1_handler             @ |- 0x00000124 -|
        defisr _dma2stream2_handler             @ |- 0x00000128 -|
        defisr _dma2stream3_handler             @ |- 0x0000012c -|
        defisr _dma2stream4_handler             @ |- 0x00000130 -|
        defisr _eth_handler                     @ |- 0x00000134 -|
        defisr _eth_wkup_handler                @ |- 0x00000138 -|
        defisr _can2tx_handler                  @ |- 0x0000013c -|
        defisr _can2rx0_handler                 @ |- 0x00000140 -|
        defisr _can2rx1_handler                 @ |- 0x00000144 -|
        defisr _can2sce_handler                 @ |- 0x00000148 -|
        defisr _otgfs_handler                   @ |- 0x0000014c -|
        defisr _dma2stream5_handler             @ |- 0x00000150 -|
        defisr _dma2stream6_handler             @ |- 0x00000154 -|
        defisr _dma2stream7_handler             @ |- 0x00000158 -|
        defisr _usart6_handler                  @ |- 0x0000015c -|
        defisr _i2c3ev_handler                  @ |- 0x00000160 -|
        defisr _i2c3er_handler                  @ |- 0x00000164 -|
        defisr _otghsep1out_handler             @ |- 0x00000168 -|
        defisr _otghsep1in_handler              @ |- 0x0000016c -|
        defisr _otghswkup_handler               @ |- 0x00000170 -|
        defisr _otghs_handler                   @ |- 0x00000174 -|
        defisr _dcmi_handler                    @ |- 0x00000178 -|
        defisr _cryp_handler                    @ |- 0x0000017c -|
        defisr _hashrng_handler                 @ |- 0x00000180 -|
        defisr _fpu_handler                     @ |- 0x00000184 -|
        defisr _uart7_handler                   @ |- 0x00000188 -|
        defisr _uart8_handler                   @ |- 0x0000018c -|
        defisr _spi4_handler                    @ |- 0x00000190 -|
        defisr _spi5_handler                    @ |- 0x00000194 -|
        defisr _spi6_handler                    @ |- 0x00000198 -|
        defisr _sai1_handler                    @ |- 0x0000019c -|
        defisr _lcdtft_handler                  @ |- 0x000001a0 -|
        defisr _lcdtfterror_handler             @ |- 0x000001a4 -|
        defisr _dma2d_handler                   @ |- 0x000001a8 -|
        defisr _sai2_handler                    @ |- 0x000001ac -|
        defisr _quadspi_handler                 @ |- 0x000001b0 -|
        defisr _lptimer1_handler                @ |- 0x000001b4 -|
        defisr _hdmicec_handler                 @ |- 0x000001b8 -|
        defisr _i2c4ev_handler                  @ |- 0x000001bc -|
        defisr _i2c4er_handler                  @ |- 0x000001c0 -|
        defisr _spdifrx_handler                 @ |- 0x000001c4 -|
        defisr _dsihost_handler                 @ |- 0x000001c8 -|
        defisr _dfsdm1flt0_handler              @ |- 0x000001cc -|
        defisr _dfsdm1flt1_handler              @ |- 0x000001d0 -|
        defisr _dfsdm1flt2_handler              @ |- 0x000001d4 -|
        defisr _dfsdm1flt3_handler              @ |- 0x000001d8 -|
        defisr _sdmmc2_handler                  @ |- 0x000001dc -|
        defisr _can3tx_handler                  @ |- 0x000001e0 -|
        defisr _can3rx0_handler                 @ |- 0x000001e4 -|
        defisr _can3rx1_handler                 @ |- 0x000001e8 -|
        defisr _can3sce_handler                 @ |- 0x000001ec -|
        defisr _jpeg_handler                    @ |- 0x000001f0 -|
        defisr _mdios_handler                   @ |- 0x000001f4 -|

        .text
        .balign 4
        .global _default_handler
        .type _default_handler, %function
_default_handler:
        bkpt
        b.n _default_handler

        .end
