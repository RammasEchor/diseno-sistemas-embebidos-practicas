#include "pwm_service.h"

static int static_pulse_ms = 50;
static int static_period_ms = 100;

LOG_MODULE_REGISTER(pwm_service, LOG_LEVEL_INF);

void static pwm_service_set_config();

void pwm_service_init(void) {
    pwm_hal_init();
    pwm_service_set_config();
}

void pwm_service_set_pulse(int pulse_ms) {
    if (pulse_ms > 0) {
        static_pulse_ms = pulse_ms;
    }
    LOG_INF("pulse: %d ms", static_pulse_ms);
    pwm_service_set_config();
}

void pwm_service_set_period(int period_ms) {
    if (period_ms > 0) {
        static_period_ms = period_ms;
    }
    LOG_INF("period: %d ms", static_period_ms);
    pwm_service_set_config();
}

void pwm_service_increment_pulse(int ms_add) {
    pwm_service_set_pulse(static_pulse_ms + ms_add);
}

void pwm_service_decrement_pulse(int ms_dec) {
    pwm_service_set_pulse(static_pulse_ms - ms_dec);
}

void pwm_service_increment_period(int ms_add) {
    pwm_service_set_period(static_period_ms + ms_add);
}

void pwm_service_decrement_period(int ms_dec) {
    pwm_service_set_period(static_period_ms - ms_dec);
}

void static pwm_service_set_config() {
    LOG_INF("duty cycle: %d %%", (static_pulse_ms * 100) / static_period_ms);
    pwm_hal_set(PWM_CHANN_ZERO, static_period_ms, static_pulse_ms);
}