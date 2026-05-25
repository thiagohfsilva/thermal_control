#pragma once

#include "esp_err.h"

esp_err_t ntc_sensor_init(void);
esp_err_t ntc_sensor_read_temperature(float *temperature_c);
