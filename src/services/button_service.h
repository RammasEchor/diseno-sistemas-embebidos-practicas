#include <zephyr/drivers/gpio.h>

typedef void (*button_callback) (void);

struct button_callbacks {
    button_callback check_power_button_pressed;
    button_callback toggle_led_pressed;
    button_callback make_led_brighter;
    button_callback make_led_darker;
    button_callback make_led_blink_slower;
    button_callback make_led_blink_faster;
};

struct button {
    int id;
    button_callback callback;
};

typedef enum {
    BUTTON_ONE,
    BUTTON_TWO,
    BUTTON_THREE,
    BUTTON_FOUR
} BUTTONS;

void button_service_init(const struct button_callbacks*);
void button_service_add_interruption(const int id, const button_callback callback);
void button1_service_interrupt_handler(const struct device* dev, struct gpio_callback* cb, uint32_t pins);
void button2_service_interrupt_handler(const struct device* dev, struct gpio_callback* cb, uint32_t pins);
void button3_service_interrupt_handler(const struct device* dev, struct gpio_callback* cb, uint32_t pins);
void button4_service_interrupt_handler(const struct device* dev, struct gpio_callback* cb, uint32_t pins);