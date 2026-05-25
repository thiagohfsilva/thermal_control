#include "thermal.h"

#include "modules/common/config.h"
#include "modules/control/filter.h"
#include "modules/control/thermal_control.h"
#include "modules/drivers/gpio_drv.h"
#include "modules/drivers/pwm_drv.h"
#include "modules/safety/safety.h"
#include "modules/sensors/ntc_sensor.h"

#include "esp_err.h"

#include <stdbool.h>

static filter_t s_temperature_filter;
static thermal_status_t s_status = {
    .temperature_c = 0.0f,
    .filtered_temperature_c = 0.0f,
    .setpoint_c = THERMAL_DEFAULT_SETPOINT_C,
    .duty_percent = 0.0f,
    .app_state = APP_STATE_INIT,
    .safety_state = SAFETY_STATE_OK,
    .sensor_valid = false,
};
static bool s_initialized;

esp_err_t thermal_init(void)
{
    if (s_initialized) {
        return ESP_OK;
    }

    esp_err_t ret = gpio_drv_init();
    if (ret != ESP_OK) {
        return ret;
    }

    ret = pwm_drv_init();
    if (ret != ESP_OK) {
        return ret;
    }

    ret = ntc_sensor_init();
    if (ret != ESP_OK) {
        return ret;
    }

    ret = filter_init(&s_temperature_filter, 0.2f);
    if (ret != ESP_OK) {
        return ret;
    }

    ret = thermal_control_init();
    if (ret != ESP_OK) {
        return ret;
    }

    ret = safety_init();
    if (ret != ESP_OK) {
        return ret;
    }

    ret = thermal_task_start();
    if (ret != ESP_OK) {
        return ret;
    }

    s_initialized = true;
    return ESP_OK;
}

esp_err_t thermal_get_status(thermal_status_t *status)
{
    if (status == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    *status = s_status;
    return ESP_OK;
}

esp_err_t thermal_set_setpoint(float setpoint_c)
{
    if (setpoint_c < THERMAL_MIN_SETPOINT_C ||
        setpoint_c > THERMAL_MAX_SETPOINT_C) {
        return ESP_ERR_INVALID_ARG;
    }

    s_status.setpoint_c = setpoint_c;
    return ESP_OK;
}

esp_err_t thermal_execute_cycle(void)
{
    float temperature_c = 0.0f;
    esp_err_t ret = ntc_sensor_read_temperature(&temperature_c);
    const bool sensor_valid = ret == ESP_OK;

    s_status.sensor_valid = sensor_valid;
    if (sensor_valid) {
        s_status.temperature_c = temperature_c;

        ret = filter_update(
            &s_temperature_filter,
            temperature_c,
            &s_status.filtered_temperature_c);
        if (ret != ESP_OK) {
            return ret;
        }
    }

    return ESP_OK;
}
