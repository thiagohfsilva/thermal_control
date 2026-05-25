#pragma once

#include "esp_err.h"

esp_err_t pwm_drv_init(void);
esp_err_t pwm_drv_set_duty(float duty_percent);
