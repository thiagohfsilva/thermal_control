#include "ntc_sensor.h"

#include "modules/common/config.h"
#include "modules/drivers/adc_drv.h"

#include "modules/common/defines.h"

#include "esp_err.h"

#include <stdbool.h>
#include <math.h>

static float ntc_sensor_raw_to_voltage(int raw_value)
{
    return ((float)raw_value / THERMAL_NTC_ADC_MAX_RAW) *
           THERMAL_NTC_ADC_REFERENCE_VOLTAGE;
}

static bool ntc_sensor_raw_is_valid(int raw_value)
{
    return raw_value > 0 &&
           (float)raw_value < THERMAL_NTC_ADC_MAX_RAW;
}

static esp_err_t ntc_sensor_voltage_to_resistance(
    float voltage, float *resistance_ohm)
{
    if (resistance_ohm == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    if (voltage <= 0.0f ||
        voltage >= THERMAL_NTC_ADC_REFERENCE_VOLTAGE) {
        return ESP_ERR_INVALID_RESPONSE;
    }

    *resistance_ohm =
        (THERMAL_NTC_SERIES_RESISTOR_OHM * voltage) /
        (THERMAL_NTC_ADC_REFERENCE_VOLTAGE - voltage);

    return ESP_OK;
}

static esp_err_t ntc_sensor_resistance_to_temperature(
    float resistance_ohm, float *temperature_c)
{
    if (temperature_c == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    if (resistance_ohm <= 0.0f) {
        return ESP_ERR_INVALID_RESPONSE;
    }

    const float nominal_temperature_k =
        THERMAL_NTC_NOMINAL_TEMPERATURE_C +
        THERMAL_CELSIUS_TO_KELVIN_OFFSET;
    const float inverse_temperature_k =
        (1.0f / nominal_temperature_k) +
        (logf(resistance_ohm / THERMAL_NTC_NOMINAL_RESISTANCE_OHM) /
         THERMAL_NTC_BETA_COEFFICIENT);

    *temperature_c =
        (1.0f / inverse_temperature_k) -
        THERMAL_CELSIUS_TO_KELVIN_OFFSET;

    return ESP_OK;
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

    int raw_value = 0;
    esp_err_t ret = adc_drv_read_raw(&raw_value);
    if (ret != ESP_OK) {
        return ret;
    }

    if (!ntc_sensor_raw_is_valid(raw_value)) {
        return ESP_ERR_INVALID_RESPONSE;
    }

    const float voltage = ntc_sensor_raw_to_voltage(raw_value);
    float resistance_ohm = 0.0f;

    ret = ntc_sensor_voltage_to_resistance(voltage, &resistance_ohm);
    if (ret != ESP_OK) {
        return ret;
    }

    return ntc_sensor_resistance_to_temperature(
        resistance_ohm, temperature_c);
}
