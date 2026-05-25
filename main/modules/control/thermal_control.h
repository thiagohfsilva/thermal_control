#pragma once

#include "esp_err.h"

esp_err_t thermal_control_init(void);
esp_err_t thermal_control_reset(void);
esp_err_t thermal_control_update(
    float setpoint_c,
    float temperature_c,
    float period_s,
    float *duty_percent);
