#include "apploader.h"
#include "memory_map.h"
#include "libopencm3/stm32/rcc.h"
#include "libopencm3/stm32/gpio.h"

///*************************************************************************************************
/// Private functions - declaration.
///*************************************************************************************************
///
/// \brief Transfers control to another image.
///
/// This function sets up the stack pointer and branches to a specified
/// program counter (PC) address, effectively starting execution of an
/// image.
///
/// \param[in] pc The program counter address to branch to.
/// \param[in] sp The stack pointer value to initialize.
///
static void jump(uint32_t pc, uint32_t sp);

///
/// \brief Turns the LED on.
///
static void led_on(void);

///
/// \brief Turns the LED off.
///
static void led_off(void);

///*************************************************************************************************
/// Private functions - definition.
///*************************************************************************************************
__attribute__((naked))
static void jump(uint32_t pc, uint32_t sp)
{
    __asm("                                             \n\
          .syntax unified                               \n\
          .cpu cortex-m7                                \n\
          .thumb                                        \n\
          msr msp, r1 /* load r1 into MSP */            \n\
          bx r0       /* branch to the address at r0 */ \n\
    ");
}

static void led_on(void)
{
    gpio_set(GPIOA, GPIO2);
}

static void led_off(void)
{
    gpio_clear(GPIOA, GPIO2);
}

///*************************************************************************************************
/// Global functions - definition.
///*************************************************************************************************
void apploader_start(void)
{
    //led_on();

#if (defined(GHOST_FEATHER_COMMON_START_APP) && (GHOST_FEATHER_COMMON_START_APP == 1))
    uint32_t *img = (uint32_t*)&__app_start__;
#else
    uint32_t *img = (uint32_t*)&__updater_start__;
#endif  /* GHOST_FEATHER_COMMON_START_APP */

    uint32_t img_sp = img[0];
    uint32_t img_pc = img[1];

    jump(img_pc, img_sp);

    /* Never return */
    while (1);

}
