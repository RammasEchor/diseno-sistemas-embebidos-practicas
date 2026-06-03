#include <zephyr/drivers/adc.h>

int adc_hal_init(void);
int adc_hal_read_mv(int* mv);