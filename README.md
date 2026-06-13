# led_blink

A small ESP-IDF project for the **ESP32-S3**. Each press of a push-button
advances a "ticker" through a cycle of LED states:

```text
ALL OFF → RED → GREEN → YELLOW → ALL ON → (back to ALL OFF)
```

The mapping from state to LED pins is driven by a lookup table rather than a
`switch`, so adding a state is just one more row.

## Hardware

| Signal       | GPIO | Notes                                              |
|--------------|------|----------------------------------------------------|
| Red LED      | 5    | output, LED + resistor to GND                      |
| Green LED    | 6    | output, LED + resistor to GND                      |
| Yellow LED   | 7    | output, LED + resistor to GND                      |
| Button       | 4    | input, internal pull-up; wire button to **GND**    |

The button uses the internal pull-up, so the pin reads **1** when released and
**0** when pressed. Wire one side of the button to GPIO 4 and the other to GND.

Pin assignments live in [main/led_blink.h](main/led_blink.h) (`RED_LED_GPIO`,
`GREEN_LED_GPIO`, `YELLOW_LED_GPIO`, `BUTTON_GPIO`).

## How it works

`app_main()` polls the button every 10 ms and detects the
*released → pressed* edge. On each press it advances `led_state`
(modulo `LED_STATE_COUNT`) and calls `update_leds()`, which looks the new state
up in the `led_patterns` table and writes each LED level:

```c
static const uint8_t led_patterns[LED_STATE_COUNT][LEDS_COUNT] = {
  [LED_ALL_OFF] = {0, 0, 0},
  [LED_RED]     = {1, 0, 0},
  [LED_GREEN]   = {0, 1, 0},
  [LED_YELLOW]  = {0, 0, 1},
  [LED_ALL_ON]  = {1, 1, 1},
};
```

A 50 ms delay after each handled press provides simple debouncing.

## Project layout

```text
main/
├── led_blink.c   app entry: device config, state, led_patterns table, app_main()
├── led_blink.h   central config: GPIO pins, counts, shared types, TAG
├── led.c/.h      LED GPIO primitives: init_gpio_led(), set_led_state()
├── button.c/.h   button GPIO + reading: btn_state_t, button_state(), init_gpio_button()
└── CMakeLists.txt
```

## Build, flash, monitor

Requires [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/)
(with the environment sourced, e.g. `. $IDF_PATH/export.sh`).

```bash
idf.py set-target esp32s3   # first time only
idf.py build
idf.py -p <PORT> flash monitor   # e.g. -p /dev/cu.usbmodem101
```

Exit the monitor with `Ctrl-]`. Log output is tagged `TICKER`.

## Configuration

Shared build settings are committed in
[sdkconfig.defaults](sdkconfig.defaults) (target chip, flash size). The generated
`sdkconfig` is gitignored. To change settings:

```bash
idf.py menuconfig
```

Then copy anything worth sharing into `sdkconfig.defaults`.
