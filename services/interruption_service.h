#include <zephyr/drivers/gpio.h>
typedef void (*button_callback) (void);

typedef struct {
    struct gpio_dt_spec button_id;
    button_callback callback;
} button_interruption;

void service_init_button_interruption(button_interruption* button_interruption);
void button_pressed_callback(const struct device* dev, struct gpio_callback* cb, uint32_t pins);