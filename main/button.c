#include "button.h"

btn_state_t button_state(gpio_num_t gpio) {
  return gpio_get_level(gpio) ? BTN_RELEASED : BTN_PRESSED;
}

void init_gpio_button(gpio_num_t gpio) {
  gpio_set_direction(gpio, GPIO_MODE_INPUT);
  gpio_set_pull_mode(gpio, GPIO_PULLUP_ONLY);
}
