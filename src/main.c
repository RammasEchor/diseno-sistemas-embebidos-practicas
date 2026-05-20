/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>


#define SW0_NODE	DT_ALIAS(sw0) 
#define SW1_NODE	DT_ALIAS(sw1) 
#define SW2_NODE	DT_ALIAS(sw2) 
#define SW3_NODE	DT_ALIAS(sw3) 
#define PWM_LED0    DT_ALIAS(pwm_led0)


typedef void (*interruption_func_ptr) (const struct device*, struct gpio_callback*, uint32_t);

uint64_t pwm_period = 100000000;
uint8_t pwm_pulse_width_percentage = 50;
static struct gpio_dt_spec button1 = GPIO_DT_SPEC_GET(SW0_NODE, gpios);
static struct gpio_callback button_cb_data_1;
static struct gpio_dt_spec button2 = GPIO_DT_SPEC_GET(SW1_NODE, gpios);
static struct gpio_callback button_cb_data_2;
static struct gpio_dt_spec button3 = GPIO_DT_SPEC_GET(SW2_NODE, gpios);
static struct gpio_callback button_cb_data_3;
static struct gpio_dt_spec button4 = GPIO_DT_SPEC_GET(SW3_NODE, gpios);
static struct gpio_callback button_cb_data_4;
static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(PWM_LED0);


uint64_t calculate_pulse_width_in_nanoseconds(int percentage, double hertz)
{
	double period_s = 1.0 / hertz;
	double percentage_d = (double)percentage / 100.0;
	uint64_t pulse_width_nano = (percentage_d * period_s) * 1000000000;
	return pulse_width_nano;
}

void set_pwm_for_all(uint64_t pwm_period_ns, uint64_t pulse_width_ns)
{
	pwm_set_dt(&pwm_led0, pwm_period, pulse_width_ns);
}

void button1_pressed(const struct device* dev, struct gpio_callback* cb, uint32_t pins)
{
	pwm_period = pwm_period / 2;
	double hertz = 1.0 / (((double)pwm_period) / 1000000000.0);
	set_pwm_for_all(pwm_period, calculate_pulse_width_in_nanoseconds(pwm_pulse_width_percentage, hertz));
	printk("New pwm_period: %.2fHz\n", hertz);
}

void button2_pressed(const struct device* dev, struct gpio_callback* cb, uint32_t pins)
{
	pwm_period = pwm_period * 2;
	double hertz = 1.0 / (((double)pwm_period) / 1000000000.0);
	set_pwm_for_all(pwm_period, calculate_pulse_width_in_nanoseconds(pwm_pulse_width_percentage, hertz));
	printk("New pwm_period: %.2fHz\n", hertz);
}

void button3_pressed(const struct device* dev, struct gpio_callback* cb, uint32_t pins)
{
	if (pwm_pulse_width_percentage == 0)
	{
		printk("Cannot lower pulse_width anymore: %d%%\n", pwm_pulse_width_percentage);
		return;
	}


	pwm_pulse_width_percentage = pwm_pulse_width_percentage - 10;
	double hertz = 1.0 / (((double)pwm_period) / 1000000000.0);
	set_pwm_for_all(pwm_period, calculate_pulse_width_in_nanoseconds(pwm_pulse_width_percentage, hertz));
	printk("New pwm_pulse_width: %d%%\n", pwm_pulse_width_percentage);
}

void button4_pressed(const struct device* dev, struct gpio_callback* cb, uint32_t pins)
{
	if (pwm_pulse_width_percentage == 100)
	{
		printk("Cannot add to pulse_width anymore: %d%%\n", pwm_pulse_width_percentage);
		return;
	}
		
	pwm_pulse_width_percentage = pwm_pulse_width_percentage + 10;
	double hertz = 1.0 / (((double)pwm_period) / 1000000000.0);
	set_pwm_for_all(pwm_period, calculate_pulse_width_in_nanoseconds(pwm_pulse_width_percentage, hertz));
	printk("New pwm_pulse_width: %d%%\n", pwm_pulse_width_percentage);
}


void config_button_interruption_function(struct gpio_dt_spec* button, interruption_func_ptr func, struct gpio_callback* callback_data)
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

int main(void)
{
	if (!device_is_ready(button1.port) || !device_is_ready(button2.port) || !pwm_is_ready_dt(&pwm_led0)) {
		printk("device not ready.\n");
		return -1;
	}

	double hertz = 1.0 / (((double)pwm_period) / 1000000000.0);
	set_pwm_for_all(pwm_period, calculate_pulse_width_in_nanoseconds(pwm_pulse_width_percentage, hertz));

	config_button_interruption_function(&button1, button1_pressed, &button_cb_data_1);
	config_button_interruption_function(&button2, button2_pressed, &button_cb_data_2);
	config_button_interruption_function(&button3, button3_pressed, &button_cb_data_3);
	config_button_interruption_function(&button4, button4_pressed, &button_cb_data_4);

	while (1) {
		k_sleep(K_FOREVER);
	}

	return 0;
}
