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
#include "safety.h"

#include "modules/common/config.h"

#include "esp_err.h"

static safety_state_t s_state = SAFETY_STATE_OK;

esp_err_t safety_init(void)
{
    s_state = SAFETY_STATE_OK;
    return ESP_OK;
}

esp_err_t safety_check_temperature(float temperature_c, bool sensor_valid,
                                   safety_state_t *state)
{
    if (state == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    if (!sensor_valid) {
        s_state = SAFETY_STATE_SENSOR_ERROR;
    } else if (temperature_c < THERMAL_MIN_SAFE_TEMPERATURE_C) {
        s_state = SAFETY_STATE_UNDERTEMPERATURE;
    } else if (temperature_c > THERMAL_MAX_SAFE_TEMPERATURE_C) {
        s_state = SAFETY_STATE_OVERTEMPERATURE;
    } else {
        s_state = SAFETY_STATE_OK;
    }

    *state = s_state;
    return ESP_OK;
}

esp_err_t safety_get_state(safety_state_t *state)
{
    if (state == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    *state = s_state;
    return ESP_OK;
}
