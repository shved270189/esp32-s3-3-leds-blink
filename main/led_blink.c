#include "led_blink.h"

static const uint8_t led_patterns[LED_STATE_COUNT][LEDS_COUNT] = {
  [LED_ALL_OFF] = {0, 0, 0},
  [LED_RED]     = {1, 0, 0},
  [LED_GREEN]   = {0, 1, 0},
  [LED_YELLOW]  = {0, 0, 1},
  [LED_ALL_ON]  = {1, 1, 1},
};

static device_t device = {
  .gpio_leds = {RED_LED_GPIO, GREEN_LED_GPIO, YELLOW_LED_GPIO},
  .gpio_buttons = {BUTTON_GPIO}
};

static device_state_t state = {
  .led_state = LED_ALL_OFF,
  .last_btn = BTN_RELEASED
};

void update_leds(led_state_t led_state) {
  uint8_t *leds = (uint8_t *)led_patterns[led_state];
  for (uint8_t i = 0; i < LEDS_COUNT; i++) {
    set_led_state(device.gpio_leds[i], leds[i]);
  }
}

void init_gpios(void) {
  for (uint8_t i = 0; i < LEDS_COUNT; i++) {
    init_gpio_led(device.gpio_leds[i]);
  }

  for (uint8_t i = 0; i < BUTTONS_COUNT; i++) {
    init_gpio_button(device.gpio_buttons[i]);
  }
}

void app_main(void)
{
  ESP_LOGI(TAG,"** START ** ");

  init_gpios();

  while (1) {
    btn_state_t btn = button_state(device.gpio_buttons[0]);
    if (btn == BTN_PRESSED && state.last_btn == BTN_RELEASED) {
      ESP_LOGI(TAG, "Press!");

      state.led_state = (state.led_state + 1) % LED_STATE_COUNT;
      update_leds(state.led_state);

      vTaskDelay(pdMS_TO_TICKS(50));
    }

    state.last_btn = btn;
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}
