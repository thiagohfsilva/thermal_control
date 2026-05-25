#pragma once

#include "modules/common/types.h"

#include "esp_err.h"

#include <stdbool.h>

esp_err_t safety_init(void);
esp_err_t safety_check_temperature(
    float temperature_c,
    bool sensor_valid,
    safety_state_t *state);
esp_err_t safety_get_state(safety_state_t *state);
