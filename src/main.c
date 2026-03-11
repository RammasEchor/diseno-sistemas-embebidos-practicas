/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include <zephyr/drivers/counter.h>
#include <zephyr/sys/printk.h>


 /* 1000 msec = 1 sec */

 /* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)
#define SW0_NODE	DT_ALIAS(sw0) 
#define SW1_NODE	DT_ALIAS(sw1) 
#define TIMER DT_NODELABEL(rtc0)
#define ALARM_CHANNEL_ID 0

struct counter_alarm_cfg alarm_cfg;
int prescaler = 10000;
bool led_state = true;

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec button1 = GPIO_DT_SPEC_GET(SW0_NODE, gpios);
static const struct gpio_dt_spec button2 = GPIO_DT_SPEC_GET(SW1_NODE, gpios);


void button1_pressed(const struct device* dev, struct gpio_callback* cb, uint32_t pins)
{
	prescaler = prescaler * 2;
	printk("New prescaler value: %d\n", prescaler);
}

void button2_pressed(const struct device* dev, struct gpio_callback* cb, uint32_t pins)
{
	prescaler = prescaler / 2;
	printk("New prescaler value: %d\n", prescaler);
}

static struct gpio_callback button_cb_data;
static struct gpio_callback button_cb_data_2;

static void test_counter_interrupt_fn(const struct device* counter_dev,
	uint8_t chan_id, uint32_t ticks,
	void* user_data)
{
	struct counter_alarm_cfg* config = user_data;
	uint32_t now_ticks;
	uint64_t now_usec;
	int now_sec;
	int err;

	err = counter_get_value(counter_dev, &now_ticks);
	if (!counter_is_counting_up(counter_dev)) {
		now_ticks = counter_get_top_value(counter_dev) - now_ticks;
	}

	if (err) {
		printk("Failed to read counter value (err %d)", err);
		return;
	}

	now_usec = counter_ticks_to_us(counter_dev, now_ticks);
	now_sec = (int)(now_usec / USEC_PER_SEC);

	int ret;
	ret = gpio_pin_toggle_dt(&led);
	if (ret < 0) {
		return;
	}

	led_state = !led_state;
	printk("LED state: %s\n", led_state ? "ON" : "OFF");

	/* Set a new alarm with a double length duration */
	config->ticks = prescaler;

	err = counter_set_channel_alarm(counter_dev, ALARM_CHANNEL_ID,
		user_data);
	if (err != 0) {
		printk("Alarm could not be set\n");
	}
}

int main(void)
{
	int ret;
	const struct device* const counter_dev = DEVICE_DT_GET(TIMER);
	int err;

	if (!gpio_is_ready_dt(&led) || !device_is_ready(button1.port) || !device_is_ready(counter_dev)) {
		printk("device not ready.\n");
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

	counter_start(counter_dev);

	alarm_cfg.flags = 0;
	alarm_cfg.ticks = counter_us_to_ticks(counter_dev, prescaler);
	alarm_cfg.callback = test_counter_interrupt_fn;
	alarm_cfg.user_data = &alarm_cfg;

	err = counter_set_channel_alarm(counter_dev, ALARM_CHANNEL_ID,
		&alarm_cfg);
	if (err != 0) {
		printk("Error\n");
	}

	while (1) {
		k_sleep(K_FOREVER);
	}

	return 0;
}
