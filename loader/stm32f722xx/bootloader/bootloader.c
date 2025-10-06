#include "bootloader.h"
#include "memory_map.h"
#include "timing.h"
#include "libopencm3/stm32/rcc.h"
#include "libopencm3/stm32/gpio.h"
#include "libopencm3/cm3/systick.h"

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
/// \brief Setups the Reset and Clock Control registers.
///
/// This function initializes the system's clock configuration by setting up
/// the Reset and Clock Control (RCC) registers for the desired system
/// performance and peripheral clock settings.
///
static void rcc_setup(void);

///
/// \brief Setups GPIO pins for the first bootloader.
///
/// This function initializes the General Purpose Input/Output (GPIO) pins
/// required by the first bootloader.
///
static void gpio_setup(void);

///
/// \brief Setups the system tick timer.
///
/// This function configures and starts the system tick timer (SysTick),
/// which is used for generating periodic interrupts and keeping
/// track of system time.
///
static void systick_setup(void);

///
/// \brief Turns the LED on.
///
static void led_on(void);

///
/// \brief Turn the LED off.
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

static void rcc_setup(void)
{
    rcc_clock_setup_hse(&rcc_3v3[RCC_CLOCK_3V3_216MHZ], 16);

    /* Enable clock for red led */
    rcc_periph_clock_enable(RCC_GPIOA);

    /* Enable clock for SPI1 */
    rcc_periph_clock_enable(RCC_SPI1);
}

static void gpio_setup(void)
{
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO2 | GPIO4);

    /* Set SPI1 gpios alternate function */
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, (GPIO5 | GPIO6 | GPIO7));
    gpio_set_af(GPIOA, GPIO_AF5, (GPIO5 | GPIO6 | GPIO7));
}

static void systick_setup(void)
{
    /* Prescaled processor clock */
    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);
    systick_counter_enable();
}

static void timing_setup(void)
{
    timing_init();
    timing_start();
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
void bootloader_start(void)
{
    rcc_setup();
    gpio_setup();
    systick_setup();
    timing_setup();

    uint32_t *img   = (uint32_t*)&__apploader_start__;
    uint32_t img_sp = img[0];
    uint32_t img_pc = img[1];

    jump(img_pc, img_sp);
    
    /* Never return */
    while (1);
}
