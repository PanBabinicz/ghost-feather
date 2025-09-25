#include "stm32f722xx_first_bootloader.h"
#include "stm32f722xx_memory_map.h"
#include "libopencm3/stm32/rcc.h"
#include "libopencm3/stm32/gpio.h"

///*************************************************************************************************
/// Private functions - declaration.
///*************************************************************************************************
///
/// \brief Transfers control to a secondary bootloader.
///
/// This function sets up the stack pointer and branches to a specified
/// program counter (PC) address, effectively starting execution of a
/// secondary bootloader or application. It uses inline assembly to
/// directly manipulate the MSP and perform the branch.
///
/// \param[in] pc The program counter address to branch to.
/// \param[in] sp The stack pointer value to initialize.
///
static void second_bootloader_startup(uint32_t pc, uint32_t sp);

///
/// \brief Sets the Reset and Clock Control registers.
///
/// This function initializes the system's clock configuration by setting up
/// the Reset and Clock Control (RCC) registers for the desired system
/// performance and peripheral clock settings.
///
static void rcc_setup(void);

///
/// \brief Sets GPIO pins for the first bootloader.
///
/// This function initializes the General Purpose Input/Output (GPIO) pins
/// required by the first bootloader.
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
static void second_bootloader_startup(uint32_t pc, uint32_t sp)
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
void first_bootloader_start(void)
{
    //rcc_setup();
    //gpio_setup();

    /* Turn on the blue led to signalize that it reached the first bootloader. */
    //led_on();

    uint32_t *second_bootloader_code         = (uint32_t*)&__bootrom2_start__;
    uint32_t second_bootloader_stack_pointer = second_bootloader_code[0];
    uint32_t second_bootloader_reset_handler = second_bootloader_code[1];

    second_bootloader_startup(second_bootloader_reset_handler, second_bootloader_stack_pointer);
    
    /* Never return */
    while (1);

}
