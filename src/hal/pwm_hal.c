#include "pwm_hal.h"

#define PWM_NODE DT_NODELABEL(pwm0)

const struct device* pwm_dev = DEVICE_DT_GET(PWM_NODE);

int pwm_hal_init() {
    if (!device_is_ready(pwm_dev)) {
        return 1;
    }
}

void pwm_hal_set(PWM_CHANNEL channel, int period_ms, int pulse_ms) {
    pwm_set(pwm_dev, channel, PWM_MSEC(period_ms), PWM_MSEC(pulse_ms), 0);
}