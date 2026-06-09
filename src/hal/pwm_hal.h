#pragma once

#include <zephyr/kernel.h>
#include <zephyr/drivers/pwm.h>

typedef enum {
    PWM_CHANN_ZERO,
    PWM_CHANN_ONE,
    PWM_CHANN_TWO,
    PWM_CHANN_THREE
} PWM_CHANNEL;

int pwm_hal_init(void);
void pwm_hal_set(PWM_CHANNEL channel, int period_ms, int pulse_ms);