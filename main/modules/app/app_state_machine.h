#pragma once

#include "modules/common/types.h"

#include "esp_err.h"

esp_err_t app_state_machine_init(void);
esp_err_t app_state_machine_get_state(app_state_t *state);
esp_err_t app_state_machine_set_state(app_state_t state);
esp_err_t app_state_machine_update_from_safety(safety_state_t safety_state);
