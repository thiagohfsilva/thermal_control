#include "ntc_sensor.h"

#include "modules/drivers/adc_drv.h"

#include "esp_err.h"

esp_err_t ntc_sensor_init(void)
{
    return adc_drv_init();
}

esp_err_t ntc_sensor_read_temperature(float *temperature_c)
{
    if (temperature_c == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    *temperature_c = 0.0f;
    return ESP_ERR_NOT_SUPPORTED;
}
