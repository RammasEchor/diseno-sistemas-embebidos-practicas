#include "button_service.h"
#include "adc_service.h"
#include "pwm_service.h"
#include "bluetooth_service.h"

struct system_callbacks {
    void (*check_power)(void);
    void (*led_brighter) (void);
    void (*led_darker) (void);
    void (*led_blink_slower) (void);
    void (*led_blink_faster) (void);
    void (*power_off) (void);
};

void system_init(const struct system_callbacks*);