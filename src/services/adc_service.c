#include "adc_service.h"

void adc_service_init() {
    adc_hal_init();
}

int adc_service_measure() {
    int mv;
    adc_hal_read_mv(&mv);
    return mv;
}