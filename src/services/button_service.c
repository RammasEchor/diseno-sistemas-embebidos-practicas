#include "button_service.h"
#include "interruption_hal.h"

LOG_MODULE_REGISTER(button_service, LOG_LEVEL_INF);

static struct button service_buttons[10];

const static interruption_func_ptr callbacks[10] = {
    [BUTTON_ONE] = button1_service_interrupt_handler,
    [BUTTON_TWO] = button2_service_interrupt_handler,
    [BUTTON_THREE] = button3_service_interrupt_handler,
    [BUTTON_FOUR] = button4_service_interrupt_handler
};

void button_service_init(const struct button_callbacks* bcb) {
    button_service_add_interruption(BUTTON_ONE, bcb->button1_callback);
    button_service_add_interruption(BUTTON_TWO, bcb->button2_callback);
    button_service_add_interruption(BUTTON_THREE, bcb->button3_callback);
    button_service_add_interruption(BUTTON_FOUR, bcb->button4_callback);
}

void button_service_add_interruption(const int id, const button_callback callback)
{
    service_buttons[id].id = id;
    service_buttons[id].callback = callback;
    hal_setup_interruption(id, callbacks[id]);
}

void button1_service_interrupt_handler(const struct device* dev, struct gpio_callback* cb, uint32_t pins)
{
    LOG_INF("Interrupt handler for button 1.");
    service_buttons[BUTTON_ONE].callback();
}

void button2_service_interrupt_handler(const struct device* dev, struct gpio_callback* cb, uint32_t pins)
{
    LOG_INF("Interrupt handler for button 2.");
    service_buttons[BUTTON_TWO].callback();
}

void button3_service_interrupt_handler(const struct device* dev, struct gpio_callback* cb, uint32_t pins)
{
    LOG_INF("Interrupt handler for button 3.");
    service_buttons[BUTTON_THREE].callback();
}

void button4_service_interrupt_handler(const struct device* dev, struct gpio_callback* cb, uint32_t pins)
{
    LOG_INF("Interrupt handler for button 4.");
    service_buttons[BUTTON_FOUR].callback();
}