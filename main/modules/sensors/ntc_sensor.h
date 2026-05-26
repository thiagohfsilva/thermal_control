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
 * @brief Inicializa o sensor NTC.
 *
 * @return ESP_OK Inicialização bem-sucedida.
 * @return ESP_FAIL Falha na inicialização.
 */
esp_err_t ntc_sensor_init(void);

/**
 * @brief Lê a temperatura do sensor NTC.
 *
 * @param[out] temperature_c Ponteiro para receber a temperatura (°C).
 * @return ESP_OK Temperatura lida.
 * @return ESP_ERR_INVALID_ARG Ponteiro nulo.
 * @return ESP_FAIL Falha na leitura.
 */
esp_err_t ntc_sensor_read_temperature(float *temperature_c);

/**
 * @brief Converte valor bruto do ADC em temperatura.
 *
 * @param[in] raw_value Valor bruto do ADC.
 * @param[out] temperature_c Ponteiro para receber a temperatura (°C).
 * @return ESP_OK Conversão realizada.
 * @return ESP_ERR_INVALID_ARG Ponteiro nulo.
 */
esp_err_t ntc_sensor_convert_raw(int raw_value, float *temperature_c);

/**
 * @brief Converte resistência em temperatura.
 *
 * @param[in] resistance_ohm Valor da resistência em ohms.
 * @param[out] temperature_c Ponteiro para receber a temperatura (°C).
 * @return ESP_OK Conversão realizada.
 * @return ESP_ERR_INVALID_ARG Ponteiro nulo.
 */
esp_err_t ntc_sensor_convert_resistance(float resistance_ohm,
                                        float *temperature_c);
