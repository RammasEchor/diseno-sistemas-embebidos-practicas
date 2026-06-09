#include <zephyr/logging/log.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/addr.h>
#include <zephyr/bluetooth/services/nus.h>
#include <string.h>

void bluetooth_hal_init(void);
void bluetooth_hal_send(const char*);