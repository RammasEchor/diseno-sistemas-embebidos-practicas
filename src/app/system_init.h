struct system_callbacks {
    void (*check_power)(void);
    void (*led_brighter) (void);
    void (*led_darker) (void);
    void (*led_blink_slower) (void);
    void (*led_blink_faster) (void);
};

void system_init(const struct system_callbacks*);