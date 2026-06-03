#include "adc_hal.h"

#define ADC_NODE DT_NODELABEL(adc)
/* ADC channel */
#define ADC_CHANNEL_ID         0
#define ADC_RESOLUTION         12
#define ADC_GAIN               ADC_GAIN_1_6
#define ADC_REFERENCE          ADC_REF_INTERNAL
#define ADC_ACQUISITION_TIME   ADC_ACQ_TIME_DEFAULT

static const struct device* adc_dev;

static struct adc_channel_cfg channel_cfg = {
    .gain = ADC_GAIN,
    .reference = ADC_REFERENCE,
    .acquisition_time = ADC_ACQUISITION_TIME,
    .channel_id = ADC_CHANNEL_ID,
};

int adc_hal_init(void)
{
    adc_dev = DEVICE_DT_GET(ADC_NODE);

    if (!device_is_ready(adc_dev)) {
        return -1;
    }

    return adc_channel_setup(adc_dev, &channel_cfg);
}

int adc_hal_read_mv(int* mv)
{
    int16_t sample;
    struct adc_sequence sequence = {
        .channels = BIT(0),
        .buffer = &sample,
        .buffer_size = sizeof(sample),
        .resolution = 12,
    };

    int err = adc_read(adc_dev, &sequence);
    if (err) {
        return err;
    }

    *mv = sample;
    return 0;
}