#include "gpio_driver.h"

static void gpio_enable_clock(GPIO_TypeDef *port)
{
    if (port == GPIOA) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    else if (port == GPIOB) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
    else if (port == GPIOC) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
    else if (port == GPIOD) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
    else if (port == GPIOE) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE);
    else if (port == GPIOF) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF);
    else if (port == GPIOG) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOG);
    else if (port == GPIOH) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOH);
    else if (port == GPIOI) LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOI);
}

void gpio_init(const gpio_init_t *init)
{
    LL_GPIO_InitTypeDef gpio = {0};

    gpio_enable_clock(init->port);

    gpio.Pin        = init->pin;
    gpio.Mode       = init->mode;
    gpio.OutputType = init->output_type;
    gpio.Speed      = init->speed;
    gpio.Pull       = init->pull;
    gpio.Alternate  = init->alternate;

    LL_GPIO_Init(init->port, &gpio);
}

void gpio_write(GPIO_TypeDef *port, uint32_t pin, uint8_t state)
{
    if (state)
        LL_GPIO_SetOutputPin(port, pin);
    else
        LL_GPIO_ResetOutputPin(port, pin);
}

void gpio_toggle(GPIO_TypeDef *port, uint32_t pin)
{
    LL_GPIO_TogglePin(port, pin);
}

uint8_t gpio_read(GPIO_TypeDef *port, uint32_t pin)
{
    return LL_GPIO_IsInputPinSet(port, pin) ? 1 : 0;
}

void gpio_lock(GPIO_TypeDef *port, uint32_t pin)
{
    LL_GPIO_LockPin(port, pin);
}
