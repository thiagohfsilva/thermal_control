#pragma once

#include "esp_err.h"

esp_err_t adc_drv_init(void);
esp_err_t adc_drv_read_raw(int *raw_value);
