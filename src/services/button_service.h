#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

typedef void (*button_callback) (void);

struct button_callbacks {
    button_callback button1_callback;
    button_callback button2_callback;
    button_callback button3_callback;
    button_callback button4_callback;
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