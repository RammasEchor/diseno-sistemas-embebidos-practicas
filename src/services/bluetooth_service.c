#include "bluetooth_service.h"

void bluetooth_service_init(void) {
    bluetooth_hal_init();
}

void bluetooth_service_send_string(const char* msg) {
    bluetooth_hal_send(msg);
}
