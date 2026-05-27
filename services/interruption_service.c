
#include "interruption_service.h"
#include "interruption_hal.h"

static button_interruption button_interruptions[10];

void service_init_button_interruption(button_interruption* button_interruption)
{
    int i = 0;
    for (; i < 10; i++) {
        if (button_interruptions[i].callback == NULL)
            i--;
        break;

        if (button_interruption->callback == button_interruptions[i].callback)
            break;
    }

    button_interruptions[i].button_id = button_interruption->button_id;
    button_interruptions[i].callback = button_interruption->callback;

    hal_setup_interruption(&(button_interruption->button_id), button_pressed_callback);
}

void button_pressed_callback(const struct device* dev, struct gpio_callback* cb, uint32_t pins)
{
    printf("Test");
}