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

#include "modules/common/config.h"
#include "modules/common/types.h"
#include "modules/thermal/thermal.h"

#include "esp_err.h"
#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <stdbool.h>

static const char *TAG = "thermal_logger";

static void logger_task(void *arg)
{
    (void)arg;

    while (true) {
        thermal_status_t status;
        if (thermal_get_status(&status) == ESP_OK) {
            ESP_LOGI(
                TAG,
                "temp=%.2fC filtered=%.2fC setpoint=%.2fC duty=%.2f%% app=%d safety=%d valid=%d",
                status.temperature_c, status.filtered_temperature_c,
                status.setpoint_c, status.duty_percent, status.app_state,
                status.safety_state, status.sensor_valid);
        }

        vTaskDelay(pdMS_TO_TICKS(THERMAL_LOG_PERIOD_MS));
    }
}

esp_err_t logger_task_start(void)
{
    BaseType_t result =
        xTaskCreate(logger_task, "logger", LOGGER_TASK_STACK_SIZE, NULL,
                    LOGGER_TASK_PRIORITY, NULL);

    return result == pdPASS ? ESP_OK : ESP_ERR_NO_MEM;
}
