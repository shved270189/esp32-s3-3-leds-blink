#pragma once

#include "esp_log.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "led.h"
#include "button.h"

#define ARRAY_LEN(a) (sizeof(a) / sizeof((a)[0]))

#define RED_LED_GPIO GPIO_NUM_5
#define GREEN_LED_GPIO GPIO_NUM_6
#define YELLOW_LED_GPIO GPIO_NUM_7
#define BUTTON_GPIO GPIO_NUM_4

#define TAG "TICKER"

#define LEDS_COUNT 3
#define BUTTONS_COUNT 1

typedef enum {
  LED_ALL_OFF = 0,
  LED_RED,
  LED_GREEN,
  LED_YELLOW,
  LED_ALL_ON,
  LED_STATE_COUNT
} led_state_t;

typedef struct {
    led_state_t led_state;
    btn_state_t last_btn;
} device_state_t;

typedef struct {
    gpio_num_t gpio_leds[LEDS_COUNT];
    gpio_num_t gpio_buttons[BUTTONS_COUNT];
} device_t;
