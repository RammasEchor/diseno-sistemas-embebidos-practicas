#include "bluetooth_hal.h"

LOG_MODULE_REGISTER(bluetooth_hal, LOG_LEVEL_INF);

static const struct bt_data ad[] = {
   BT_DATA_BYTES(BT_DATA_FLAGS,
                  (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA(BT_DATA_NAME_COMPLETE, CONFIG_BT_DEVICE_NAME,
            sizeof(CONFIG_BT_DEVICE_NAME) - 1),
};

static const struct bt_le_adv_param* adv_param =
BT_LE_ADV_PARAM(BT_LE_ADV_OPT_CONN,
    BT_GAP_ADV_FAST_INT_MIN_2,
    BT_GAP_ADV_FAST_INT_MAX_2,
    NULL);

static struct bt_nus_cb nus_cb = {};

void bluetooth_hal_init() {
    int err = bt_enable(NULL);
    if (err) {
        LOG_INF("Bluetooth init failed (%d)", err);
        return;
    }

    LOG_INF("Bluetooth initialized");

    err = bt_le_adv_start(adv_param,
        ad, ARRAY_SIZE(ad),
        NULL, 0);

    if (err) {
        LOG_INF("Bluetooth advertising failed: (%d)", err);
        return;
    }
    else {
        LOG_INF("Bluetooth advertising");
    }

    err = bt_nus_init(&nus_cb);
    if (err) {
        LOG_INF("NUS init failed (%d)", err);
        return;
    }
}

void bluetooth_hal_send(const char* msg) {
    bt_nus_send(NULL, msg, strlen(msg));
}
