#include"uart_hal.h"

const struct device* uart_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_shell_uart));

void uart_send_string(const char* str)
{
    while (*str) {
        uart_poll_out(uart_dev, *str++);
    }
}