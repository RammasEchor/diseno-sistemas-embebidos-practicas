#include <zephyr/kernel.h>
#include <zephyr/drivers/pwm.h>

typedef enum {
    PWM_CHANNEL_ZERO,
    PWM_CHANNEL_ONE,
    PWM_CHANNEL_TWO,
    PWM_CHANNEL_THREE
} PWM_CHANNEL;

int pwm_hal_init(void);
void pwm_hal_set(PWM_CHANNEL channel, int period_ms, int pulse_ms);