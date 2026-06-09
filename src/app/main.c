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
#include <zephyr/sys/poweroff.h>

#include "voltage_meter.h"
#include "indicator_led.h"
#include "bluetooth_conn.h"
#include "system_init.h"

LOG_MODULE_REGISTER(app, LOG_LEVEL_INF);

void check_power(void) {
	int volts = measure_voltage();
	LOG_INF("%d", volts);
}

void led_brighter(void) {
	const char* msg_ptr = "Making LED brighter";
	bluetooth_send(msg_ptr);
	make_led_brighter();
}

void led_darker(void) {
	const char* msg_ptr = "Making LED darker";
	bluetooth_send(msg_ptr);
	make_led_darker();
}

void led_blink_slower(void) {
	const char* msg_ptr = "Making LED slower";
	bluetooth_send(msg_ptr);
	make_led_blink_slower();
}

void led_blink_faster(void) {
	const char* msg_ptr = "Making LED faster";
	bluetooth_send(msg_ptr);
	make_led_blink_faster();
}

void power_off(void) {
	LOG_INF("Powering off\n");
	sys_poweroff();
}

static struct system_callbacks cb = {
		.led_brighter = led_brighter,
		.led_darker = led_darker,
		.led_blink_slower = led_blink_slower,
		.led_blink_faster = led_blink_faster,
		.power_off = power_off
};

int main(void)
{
	system_init(&cb);

	return 0;
}
