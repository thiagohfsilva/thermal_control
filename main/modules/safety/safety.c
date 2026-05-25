#include "safety.h"

#include "modules/common/config.h"

#include "esp_err.h"

static safety_state_t s_state = SAFETY_STATE_OK;

esp_err_t safety_init(void)
{
    s_state = SAFETY_STATE_OK;
    return ESP_OK;
}

esp_err_t safety_check_temperature(
    float temperature_c,
    bool sensor_valid,
    safety_state_t *state)
{
    if (state == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    if (temperature_c < THERMAL_MIN_SAFE_TEMPERATURE_C) {
        s_state = SAFETY_STATE_UNDERTEMPERATURE;
    } else if (temperature_c > THERMAL_MAX_SAFE_TEMPERATURE_C) {
        s_state = SAFETY_STATE_OVERTEMPERATURE;
    } else {
        s_state = SAFETY_STATE_OK;
    }

    *state = s_state;
    return ESP_OK;
}

esp_err_t safety_get_state(safety_state_t *state)
{
    if (state == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    *state = s_state;
    return ESP_OK;
}
