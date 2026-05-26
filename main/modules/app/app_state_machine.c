/*
 * Copyright (C) 2026 Thiago Henrique Ferreira da Silva
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Author: Thiago Henrique Ferreira da Silva
 */
#include "esp_log.h"
#include "app_state_machine.h"

#include "esp_err.h"

static app_state_t s_app_state = APP_STATE_INIT;
static const char *TAG = "APP_SM";

esp_err_t app_state_machine_init(void)
{
    s_app_state = APP_STATE_INIT;
    ESP_LOGI(TAG, "App state machine initialized");
    return ESP_OK;
}

esp_err_t app_state_machine_get_state(app_state_t *state)
{
    if (state == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    *state = s_app_state;
    return ESP_OK;
}

esp_err_t app_state_machine_set_state(app_state_t state)
{
    if (s_app_state == APP_STATE_SHUTDOWN) {
        ESP_LOGW(TAG, "Cannot change state: already in SHUTDOWN");
        return ESP_ERR_INVALID_STATE;
    }

    if (s_app_state == APP_STATE_FAULT && state == APP_STATE_RUNNING) {
        ESP_LOGW(TAG, "Cannot transition from FAULT to RUNNING");
        return ESP_ERR_INVALID_STATE;
    }

    ESP_LOGI(TAG, "State changed: %d -> %d", s_app_state, state);
    s_app_state = state;
    return ESP_OK;
}

esp_err_t app_state_machine_update_from_safety(safety_state_t safety_state)
{
    if (safety_state != SAFETY_STATE_OK) {
        ESP_LOGW(TAG, "Safety not OK, setting app state to FAULT");
        s_app_state = APP_STATE_FAULT;
    }

    return ESP_OK;
}
