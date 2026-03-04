/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

 /* 1000 msec = 1 sec */

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)
#define SW0_NODE	DT_ALIAS(sw0) 
#define SW1_NODE	DT_ALIAS(sw1) 

int sleep_time = 100;

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec button1 = GPIO_DT_SPEC_GET(SW0_NODE, gpios);
static const struct gpio_dt_spec button2 = GPIO_DT_SPEC_GET(SW1_NODE, gpios);


void button1_pressed(const struct device* dev, struct gpio_callback* cb, uint32_t pins)
{
	sleep_time = sleep_time * 2;
}

void button2_pressed(const struct device* dev, struct gpio_callback* cb, uint32_t pins)
{
	sleep_time = sleep_time / 2;
}

static struct gpio_callback button_cb_data;
static struct gpio_callback button_cb_data_2;

int main(void)
{
	int ret;
	bool led_state = true;

	if (!gpio_is_ready_dt(&led) || !device_is_ready(button1.port)) {
		return -1;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}
	ret = gpio_pin_configure_dt(&button1, GPIO_INPUT);
	if (ret < 0) {
		return -1;
	}
	ret = gpio_pin_configure_dt(&button2, GPIO_INPUT);
	if (ret < 0) {
		return -1;
	}
	ret = gpio_pin_interrupt_configure_dt(&button1, GPIO_INT_EDGE_RISING);
	if (ret < 0) {
		return -1;
	}
	ret = gpio_pin_interrupt_configure_dt(&button2, GPIO_INT_EDGE_FALLING);
	if (ret < 0) {
		return -1;
	}

	gpio_init_callback(&button_cb_data, button1_pressed, BIT(button1.pin));
	gpio_add_callback(button1.port, &button_cb_data);

	gpio_init_callback(&button_cb_data_2, button2_pressed, BIT(button2.pin));
	gpio_add_callback(button2.port, &button_cb_data_2);

	while (1) {
		ret = gpio_pin_toggle_dt(&led);
		if (ret < 0) {
			return 0;
		}

		led_state = !led_state;
		printf("LED state: %s\n", led_state ? "ON" : "OFF");
		k_msleep(sleep_time);
	}
	return 0;
}
