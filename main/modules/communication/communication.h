#pragma once

#include "modules/common/types.h"

#include "esp_err.h"

esp_err_t communication_init(void);
esp_err_t communication_task_start(void);
esp_err_t communication_get_status(thermal_status_t *status);
esp_err_t communication_set_setpoint(float setpoint_c);
