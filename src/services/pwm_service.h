#include "pwm_hal.h"
#include <zephyr/logging/log.h>

void pwm_service_init(void);
void pwm_service_set_pulse(int);
void pwm_service_set_period(int);
void pwm_service_increment_pulse(int);
void pwm_service_decrement_pulse(int);
void pwm_service_increment_period(int);
void pwm_service_decrement_period(int);