#pragma once

#include "esp_err.h"

#include <stdbool.h>

esp_err_t gpio_drv_init(void);
esp_err_t gpio_drv_set_enable(bool enabled);
esp_err_t gpio_drv_set_fault_indicator(bool active);
