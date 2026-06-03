#include "indicator_led.h"

void make_led_brighter(void) {
    pwm_service_increment_pulse(10);
}

void make_led_darker(void) {
    pwm_service_decrement_pulse(10);
}

void make_led_blink_faster(void) {
    pwm_service_decrement_period(10);
}

void make_led_blink_slower(void) {
    pwm_service_increment_period(10);
}