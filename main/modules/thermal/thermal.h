#pragma once

#include "modules/common/types.h"

#include "esp_err.h"

esp_err_t thermal_init(void);
esp_err_t thermal_get_status(thermal_status_t *status);
esp_err_t thermal_set_setpoint(float setpoint_c);
esp_err_t thermal_execute_cycle(void);
esp_err_t thermal_task_start(void);
