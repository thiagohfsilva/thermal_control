#pragma once

#include "esp_err.h"

esp_err_t ntc_sensor_init(void);
esp_err_t ntc_sensor_read_temperature(float *temperature_c);
esp_err_t ntc_sensor_convert_raw(int raw_value, float *temperature_c);
esp_err_t ntc_sensor_convert_resistance(float resistance_ohm,
                                        float *temperature_c);
