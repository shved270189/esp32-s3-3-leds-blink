#pragma once

#include <stdint.h>
#include "driver/gpio.h"

void set_led_state(gpio_num_t gpio, uint8_t on);
void init_gpio_led(gpio_num_t gpio);
