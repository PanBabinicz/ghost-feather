#ifndef _GMOCK_LIBOPENCM3_GPIO_H
#define _GMOCK_LIBOPENCM3_GPIO_H

#include <stdint.h>

#define GPIOA       (GPIO_PORT_A)
#define GPIOB       (GPIO_PORT_B)
#define GPIOC       (GPIO_PORT_C)
#define GPIOD       (GPIO_PORT_D)
#define GPIOE       (GPIO_PORT_E)
#define GPIOF       (GPIO_PORT_F)

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

///
/// \breif The gpio port type.
///
typedef enum gpio_port
{
    GPIO_PORT_A = 0,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_D,
    GPIO_PORT_E,
    GPIO_PORT_F,
    GPIO_PORT_TOTAL,
} gpio_port_t;

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

static uint32_t GPIO_BSRR_REG[GPIO_PORT_TOTAL];

///
/// \breif Mock implementation of gpio_clear function.
///
static inline void gpio_clear(uint32_t gpioport, uint16_t gpios)
{
    GPIO_BSRR_REG[gpioport] = (gpios << 16);
}

///
/// \breif Mock implementation of gpio_set function.
///
static inline void gpio_set(uint32_t gpioport, uint16_t gpios)
{
    GPIO_BSRR_REG[gpioport] = (gpios << 16);
}

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _GMOCK_LIBOPENCM3_GPIO_H */
