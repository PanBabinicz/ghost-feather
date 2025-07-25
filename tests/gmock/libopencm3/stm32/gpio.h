#ifndef _GMOCK_LIBOPENCM3_GPIO_H
#define _GMOCK_LIBOPENCM3_GPIO_H

#include <stdint.h>

#define GPIO_BASE   (0x40006000U)

#define GPIO_P(i)   (GPIO_BASE + (0x24 * (i)))
#define GPIO_PA	    (GPIO_P(0))
#define GPIO_PB     (GPIO_P(1))
#define GPIO_PC     (GPIO_P(2))
#define GPIO_PD     (GPIO_P(3))
#define GPIO_PE     (GPIO_P(4))
#define GPIO_PF     (GPIO_P(5))

#define GPIOA       (GPIO_PA)
#define GPIOB       (GPIO_PB)
#define GPIOC       (GPIO_PC)
#define GPIOD       (GPIO_PD)
#define GPIOE       (GPIO_PE)
#define GPIOF       (GPIO_PF)

#define GPIO0       (0x01 << 0x00)
#define GPIO1       (0x01 << 0x01)
#define GPIO2       (0x01 << 0x02)
#define GPIO3       (0x01 << 0x03)
#define GPIO4       (0x01 << 0x04)
#define GPIO5       (0x01 << 0x05)
#define GPIO6       (0x01 << 0x06)
#define GPIO7       (0x01 << 0x07)
#define GPIO8       (0x01 << 0x08)
#define GPIO9       (0x01 << 0x09)
#define GPIO10      (0x01 << 0x0a)
#define GPIO11      (0x01 << 0x0b)
#define GPIO12      (0x01 << 0x0c)
#define GPIO13      (0x01 << 0x0d)
#define GPIO14      (0x01 << 0x0e)
#define GPIO15      (0x01 << 0x0f)
#define GPIO_ALL    (0xffff)

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \breif Mock implementation of gpio_clear function.
///
static inline void gpio_clear(uint32_t gpioport, uint16_t gpios)
{
    return;
}

///
/// \breif Mock implementation of gpio_set function.
///
static inline void gpio_set(uint32_t gpioport, uint16_t gpios)
{
    return;
}

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _GMOCK_LIBOPENCM3_GPIO_H */
