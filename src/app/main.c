/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/pwm.h>

#include "voltage_meter.h"
#include "indicator_led.h"
#include "system_init.h"

#define PWM_PERIOD_NS 1000000U
LOG_MODULE_REGISTER(app, LOG_LEVEL_INF);

void check_power(void) {
	int volts = measure_voltage();
	LOG_INF("%d", volts);
}

void led_brighter(void) {
	make_led_brighter();
}

void led_darker(void) {
	make_led_darker();
}

void led_blink_slower(void) {
	make_led_blink_slower();
}

void led_blink_faster(void) {
	make_led_blink_faster();
}

int main(void)
{
	struct system_callbacks cb = {
		.led_brighter = led_brighter,
		.led_darker = led_darker,
		.led_blink_slower = led_blink_slower,
		.led_blink_faster = led_blink_faster
	};
	system_init(&cb);

	return 0;
}
