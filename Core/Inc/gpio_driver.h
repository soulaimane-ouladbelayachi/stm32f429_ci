#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_bus.h"
#include <stdint.h>

typedef enum
{
    GPIO_MODE_INPUT      = LL_GPIO_MODE_INPUT,
    GPIO_MODE_OUTPUT     = LL_GPIO_MODE_OUTPUT,
    GPIO_MODE_ALTERNATE  = LL_GPIO_MODE_ALTERNATE,
    GPIO_MODE_ANALOG     = LL_GPIO_MODE_ANALOG
} gpio_mode_t;

typedef enum
{
    GPIO_OUTPUT_PUSHPULL  = LL_GPIO_OUTPUT_PUSHPULL,
    GPIO_OUTPUT_OPENDRAIN = LL_GPIO_OUTPUT_OPENDRAIN
} gpio_output_type_t;

typedef enum
{
    GPIO_SPEED_LOW      = LL_GPIO_SPEED_FREQ_LOW,
    GPIO_SPEED_MEDIUM   = LL_GPIO_SPEED_FREQ_MEDIUM,
    GPIO_SPEED_HIGH     = LL_GPIO_SPEED_FREQ_HIGH,
    GPIO_SPEED_VERYHIGH = LL_GPIO_SPEED_FREQ_VERY_HIGH
} gpio_speed_t;

typedef enum
{
    GPIO_NO_PULL   = LL_GPIO_PULL_NO,
    GPIO_PULL_UP   = LL_GPIO_PULL_UP,
    GPIO_PULL_DOWN = LL_GPIO_PULL_DOWN
} gpio_pull_t;

typedef struct
{
    GPIO_TypeDef *port;        // GPIOA, GPIOB, ...
    uint32_t      pin;         // LL_GPIO_PIN_x
    gpio_mode_t   mode;
    gpio_output_type_t output_type;
    gpio_speed_t  speed;
    gpio_pull_t   pull;
    uint32_t      alternate;   // LL_GPIO_AF_x
} gpio_init_t;

void gpio_init(const gpio_init_t *init);
void gpio_write(GPIO_TypeDef *port, uint32_t pin, uint8_t state);
void gpio_toggle(GPIO_TypeDef *port, uint32_t pin);
uint8_t gpio_read(GPIO_TypeDef *port, uint32_t pin);
void gpio_lock(GPIO_TypeDef *port, uint32_t pin);

#endif // GPIO_DRIVER_H