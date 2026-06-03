#include "system_init.h"
#include "button_service.h"
#include "adc_service.h"
#include "pwm_service.h"

static struct button_callbacks callbacks;

void system_init(const struct system_callbacks* cb) {
    callbacks.make_led_brighter = cb->led_brighter;
    callbacks.make_led_darker = cb->led_darker;
    callbacks.make_led_blink_faster = cb->led_blink_faster;
    callbacks.make_led_blink_slower = cb->led_blink_slower;
    button_service_init(&callbacks);
    adc_service_init();
    pwm_service_init();
}