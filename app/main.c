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
#include <zephyr/drivers/gpio.h>

#include "interruption_service.h"

#define SW0_NODE	DT_ALIAS(sw0) 
#define SW1_NODE	DT_ALIAS(sw1) 
#define SW2_NODE	DT_ALIAS(sw2) 
#define SW3_NODE	DT_ALIAS(sw3) 

void button1_callback(void) {
	printf("Button1 callback");
}

int main(void)
{
	button_interruption button1_interruption = {
		.button_id = GPIO_DT_SPEC_GET(SW0_NODE, gpios),
		.callback = button1_callback
	};

	service_init_button_interruption(&button1_interruption);

	return 0;
}
