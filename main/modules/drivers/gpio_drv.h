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
#pragma once

#include "esp_err.h"

#include <stdbool.h>

/**
 * @brief Inicializa o driver de GPIO.
 *
 * @return ESP_OK Inicialização bem-sucedida.
 * @return ESP_FAIL Falha na inicialização.
 */
esp_err_t gpio_drv_init(void);

/**
 * @brief Ativa ou desativa o enable via GPIO.
 *
 * @param[in] enabled true para ativar, false para desativar.
 * @return ESP_OK Operação realizada.
 * @return ESP_FAIL Falha na operação.
 */
esp_err_t gpio_drv_set_enable(bool enabled);

/**
 * @brief Ativa ou desativa o indicador de falha via GPIO.
 *
 * @param[in] active true para ativar, false para desativar.
 * @return ESP_OK Operação realizada.
 * @return ESP_FAIL Falha na operação.
 */
esp_err_t gpio_drv_set_fault_indicator(bool active);
