#include "system_init.h"

static struct button_callbacks callbacks;

void system_init(const struct system_callbacks* cb) {
    callbacks.button1_callback = cb->led_brighter;
    callbacks.button2_callback = cb->led_darker;
    callbacks.button3_callback = cb->led_blink_faster;
    callbacks.button4_callback = cb->power_off;
    button_service_init(&callbacks);
    adc_service_init();
    pwm_service_init();
    bluetooth_service_init();
}