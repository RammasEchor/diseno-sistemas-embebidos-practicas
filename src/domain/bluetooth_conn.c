#include "bluetooth_conn.h"


void bluetooth_send(const char* msg) {
    bluetooth_service_send_string(msg);
}