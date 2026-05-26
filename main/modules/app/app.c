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
#include "app.h"

#include "modules/app/app_state_machine.h"
#include "modules/communication/communication.h"
#include "modules/logger/logger.h"
#include "modules/thermal/thermal.h"

esp_err_t app_init(void)
{
    esp_err_t ret = app_state_machine_init();
    if (ret != ESP_OK) {
        return ret;
    }

    ret = logger_init();
    if (ret != ESP_OK) {
        (void)app_state_machine_set_state(APP_STATE_FAULT);
        return ret;
    }

    ret = communication_init();
    if (ret != ESP_OK) {
        (void)app_state_machine_set_state(APP_STATE_FAULT);
        return ret;
    }

    ret = thermal_init();
    if (ret != ESP_OK) {
        (void)app_state_machine_set_state(APP_STATE_FAULT);
        return ret;
    }

    return app_state_machine_set_state(APP_STATE_RUNNING);
}
