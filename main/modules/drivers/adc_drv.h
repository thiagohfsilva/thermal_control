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

/**
 * @brief Inicializa o driver ADC.
 *
 * @return ESP_OK Inicialização bem-sucedida.
 * @return ESP_FAIL Falha na inicialização.
 */
esp_err_t adc_drv_init(void);

/**
 * @brief Lê o valor bruto do ADC.
 *
 * @param[out] raw_value Ponteiro para receber o valor lido.
 * @return ESP_OK Valor lido.
 * @return ESP_ERR_INVALID_ARG Ponteiro nulo.
 * @return ESP_FAIL Falha na leitura.
 */
esp_err_t adc_drv_read_raw(int *raw_value);
