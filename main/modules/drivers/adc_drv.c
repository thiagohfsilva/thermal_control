#include "adc_drv.h"

#include "esp_err.h"

esp_err_t adc_drv_init(void)
{
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t adc_drv_read_raw(int *raw_value)
{
    if (raw_value == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    *raw_value = 0;
    return ESP_ERR_NOT_SUPPORTED;
}
