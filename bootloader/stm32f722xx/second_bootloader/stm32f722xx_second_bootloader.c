#include "ghost_feather_common.h"
#include "stm32f722xx_second_bootloader.h"
#include "stm32f722xx_memory_map.h"
#include "libopencm3/stm32/rcc.h"
#include "libopencm3/stm32/gpio.h"

///*************************************************************************************************
/// Private functions - declaration.
///*************************************************************************************************
///
/// \brief
///
static void app_startup(uint32_t pc, uint32_t sp);

static void boot_updater_startup(uint32_t pc, uint32_t sp);

///
/// \brief Sets the Reset and Clock Control registers.
///
/// This function initializes the system's clock configuration by setting up
/// the Reset and Clock Control (RCC) registers for the desired system
/// performance and peripheral clock settings.
///
static void rcc_setup(void);

///
/// \brief Sets GPIO pins for the application.
///
/// This function initializes the General Purpose Input/Output (GPIO) pins
/// required by the application.
///
static void gpio_setup(void);

///
/// \brief Turns the LED on.
///
static void led_on(void);

///*************************************************************************************************
/// Private functions - definition.
///*************************************************************************************************
__attribute__((naked))
static void app_startup(uint32_t pc, uint32_t sp)
{
    __asm("                                             \n\
          .syntax unified                               \n\
          .cpu cortex-m7                                \n\
          .thumb                                        \n\
          msr msp, r1 /* load r1 into MSP */            \n\
          bx r0       /* branch to the address at r0 */ \n\
    ");
}

__attribute__((naked))
static void boot_updater_startup(uint32_t pc, uint32_t sp)
{
    __asm("                                             \n\
          .syntax unified                               \n\
          .cpu cortex-m7                                \n\
          .thumb                                        \n\
          msr msp, r1 /* load r1 into MSP */            \n\
          bx r0       /* branch to the address at r0 */ \n\
    ");
}

static void rcc_setup(void)
{
    rcc_periph_clock_enable(RCC_GPIOA);
}

static void gpio_setup(void)
{
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO2);
}

static void led_on(void)
{
    gpio_set(GPIOA, GPIO2);
}

///*************************************************************************************************
/// Global functions - definition.
///*************************************************************************************************
void second_bootloader_start(void)
{
    rcc_setup();
    gpio_setup();

    /* Turn on the red led to signalize that we reached the second bootloader */
    led_on();

#if (defined(GHOST_FEATHER_COMMON_START_APP) &&
            (GHOST_FEATHER_COMMON_START_APP == 1))
    uint32_t *app_code         = (uint32_t*)&__approm_start__;
    uint32_t app_stack_pointer = app_code[0];
    uint32_t app_reset_handler = app_code[1];

    app_startup(app_reset_handler, app_stack_pointer);
#else
    uint32_t *boot_updater_code         = (uint32_t*)&__ubootrom_start__;
    uint32_t boot_updater_stack_pointer = boot_updater_code[0];
    uint32_t boot_updater_reset_handler = boot_updater_code[1];

    boot_updater_startup(boot_updater_reset_handler, boot_updater_stack_pointer);
#endif  /* START_APP */
    
    /* Never return */
    while (1);

}
