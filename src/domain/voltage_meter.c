#include "voltage_meter.h"

int measure_voltage(void) {
    int value = adc_service_measure();
    return value;
}