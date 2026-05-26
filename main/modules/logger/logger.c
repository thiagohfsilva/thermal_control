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
#include "logger.h"

#include "esp_err.h"

#include <stdbool.h>

static bool s_initialized;

esp_err_t logger_init(void)
{
    if (s_initialized) {
        return ESP_OK;
    }

    esp_err_t ret = logger_task_start();
    if (ret != ESP_OK) {
        return ret;
    }

    s_initialized = true;
    return ESP_OK;
}
