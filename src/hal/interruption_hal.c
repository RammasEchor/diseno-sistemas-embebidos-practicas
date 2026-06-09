#include <zephyr/drivers/gpio.h>

#include "interruption_hal.h"
#include "buttons_hal.h"


static struct gpio_callback callback_data[10];

void hal_interruption_init() {}

void hal_setup_interruption(int id, interruption_func_ptr func)
{
    hal_configure_button_interruption(&(buttons[id]), func, &(callback_data[id]));
}

void hal_configure_button_interruption(struct gpio_dt_spec* button, interruption_func_ptr func, struct gpio_callback* callback_data)
{
    int ret;
    ret = gpio_pin_configure_dt(button, GPIO_INPUT);
    if (ret < 0) {
        return;
    }

    ret = gpio_pin_interrupt_configure_dt(button, GPIO_INT_EDGE_RISING);
    if (ret < 0) {
        return;
    }

    gpio_init_callback(callback_data, func, BIT(button->pin));
    gpio_add_callback(button->port, callback_data);
}