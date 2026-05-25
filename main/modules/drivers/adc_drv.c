#include "adc_drv.h"

#include "modules/common/config.h"

#include "esp_adc/adc_oneshot.h"
#include "esp_err.h"

#include <stdbool.h>

static adc_oneshot_unit_handle_t s_adc_handle;
static bool s_initialized;

esp_err_t adc_drv_init(void)
{
    if (s_initialized) {
        return ESP_OK;
    }

    adc_oneshot_unit_init_cfg_t unit_config = {
        .unit_id = THERMAL_NTC_ADC_UNIT,
    };

    esp_err_t ret = adc_oneshot_new_unit(&unit_config, &s_adc_handle);
    if (ret != ESP_OK) {
        return ret;
    }

    adc_oneshot_chan_cfg_t channel_config = {
        .atten = THERMAL_NTC_ADC_ATTEN,
        .bitwidth = THERMAL_NTC_ADC_BITWIDTH,
    };

    ret = adc_oneshot_config_channel(
        s_adc_handle, THERMAL_NTC_ADC_CHANNEL, &channel_config);
    if (ret != ESP_OK) {
        return ret;
    }

    s_initialized = true;
    return ESP_OK;
}

esp_err_t adc_drv_read_raw(int *raw_value)
{
    if (raw_value == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    *raw_value = 0;
    return ESP_ERR_NOT_SUPPORTED;
}
