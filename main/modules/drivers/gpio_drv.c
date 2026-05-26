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
#include "gpio_drv.h"

#include "modules/common/config.h"

#include "driver/gpio.h"
#include "esp_err.h"

esp_err_t gpio_drv_init(void)
{
    if (THERMAL_ENABLE_GPIO != GPIO_NUM_NC) {
        gpio_config_t enable_config = {
            .pin_bit_mask = 1ULL << THERMAL_ENABLE_GPIO,
            .mode = GPIO_MODE_OUTPUT,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .intr_type = GPIO_INTR_DISABLE,
        };

        esp_err_t ret = gpio_config(&enable_config);
        if (ret != ESP_OK) {
            return ret;
        }

        ret = gpio_drv_set_enable(false);
        if (ret != ESP_OK) {
            return ret;
        }
    }

    if (THERMAL_FAULT_GPIO != GPIO_NUM_NC) {
        gpio_config_t fault_config = {
            .pin_bit_mask = 1ULL << THERMAL_FAULT_GPIO,
            .mode = GPIO_MODE_OUTPUT,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .intr_type = GPIO_INTR_DISABLE,
        };

        esp_err_t ret = gpio_config(&fault_config);
        if (ret != ESP_OK) {
            return ret;
        }

        ret = gpio_drv_set_fault_indicator(false);
        if (ret != ESP_OK) {
            return ret;
        }
    }

    return ESP_OK;
}

esp_err_t gpio_drv_set_enable(bool enabled)
{
    if (THERMAL_ENABLE_GPIO == GPIO_NUM_NC) {
        return ESP_OK;
    }

    return gpio_set_level(THERMAL_ENABLE_GPIO, enabled ? 1 : 0);
}

esp_err_t gpio_drv_set_fault_indicator(bool active)
{
    if (THERMAL_FAULT_GPIO == GPIO_NUM_NC) {
        return ESP_OK;
    }

    return gpio_set_level(THERMAL_FAULT_GPIO, active ? 1 : 0);
}
