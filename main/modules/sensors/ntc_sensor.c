#include "ntc_sensor.h"

#include "modules/common/config.h"
#include "modules/drivers/adc_drv.h"

#include "esp_err.h"

static float ntc_sensor_raw_to_voltage(int raw_value)
{
    return ((float)raw_value / THERMAL_NTC_ADC_MAX_RAW) *
           THERMAL_NTC_ADC_REFERENCE_VOLTAGE;
}

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
