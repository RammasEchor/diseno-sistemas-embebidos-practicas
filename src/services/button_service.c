#include "button_service.h"
#include "interruption_hal.h"

static struct button service_buttons[10];
void button1_service_interrupt_handler(const struct device* dev, struct gpio_callback* cb, uint32_t pins);

const static interruption_func_ptr callbacks[10] = {
    [BUTTON_ONE] = button1_service_interrupt_handler,
    [BUTTON_TWO] = button2_service_interrupt_handler,
    [BUTTON_THREE] = button3_service_interrupt_handler,
    [BUTTON_FOUR] = button4_service_interrupt_handler
};

void button_service_init(const struct button_callbacks* bcb) {
    button_service_add_interruption(BUTTON_ONE, bcb->make_led_brighter);
    button_service_add_interruption(BUTTON_TWO, bcb->make_led_darker);
    button_service_add_interruption(BUTTON_THREE, bcb->make_led_blink_faster);
    button_service_add_interruption(BUTTON_FOUR, bcb->make_led_blink_slower);
}

void button_service_add_interruption(const int id, const button_callback callback)
{
    service_buttons[id].id = id;
    service_buttons[id].callback = callback;
    hal_setup_interruption(id, callbacks[id]);
}

void button1_service_interrupt_handler(const struct device* dev, struct gpio_callback* cb, uint32_t pins)
{
    service_buttons[BUTTON_ONE].callback();
}

void button2_service_interrupt_handler(const struct device* dev, struct gpio_callback* cb, uint32_t pins)
{
    service_buttons[BUTTON_TWO].callback();
}

void button3_service_interrupt_handler(const struct device* dev, struct gpio_callback* cb, uint32_t pins)
{
    service_buttons[BUTTON_THREE].callback();
}

void button4_service_interrupt_handler(const struct device* dev, struct gpio_callback* cb, uint32_t pins)
{
    service_buttons[BUTTON_FOUR].callback();
}