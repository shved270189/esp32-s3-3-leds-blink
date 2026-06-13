#pragma once

#include <stdint.h>
#include "driver/gpio.h"

typedef enum {
    BTN_PRESSED = 0,
    BTN_RELEASED
} btn_state_t;

btn_state_t button_state(gpio_num_t gpio);
void init_gpio_button(gpio_num_t gpio);
