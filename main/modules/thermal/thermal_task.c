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
#include "thermal.h"

#include "modules/common/config.h"

#include "esp_err.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <stdbool.h>

static void thermal_task(void *arg)
{
    (void)arg;
    TickType_t last_wake_time = xTaskGetTickCount();

    while (true) {
        (void)thermal_execute_cycle();
        vTaskDelayUntil(&last_wake_time,
                        pdMS_TO_TICKS(THERMAL_CONTROL_PERIOD_MS));
    }
}

esp_err_t thermal_task_start(void)
{
    BaseType_t result =
        xTaskCreate(thermal_task, "thermal", THERMAL_TASK_STACK_SIZE, NULL,
                    THERMAL_TASK_PRIORITY, NULL);

    return result == pdPASS ? ESP_OK : ESP_ERR_NO_MEM;
}
