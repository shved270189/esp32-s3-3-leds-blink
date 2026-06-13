#include "led.h"

void init_gpio_led(gpio_num_t gpio) {
  gpio_set_direction(gpio, GPIO_MODE_OUTPUT);
}

void set_led_state(gpio_num_t gpio, uint8_t on) {
  gpio_set_level(gpio, on ? 1 : 0);
}
