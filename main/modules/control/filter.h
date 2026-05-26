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

typedef struct {
    float alpha;
    float value;
    bool initialized;
} filter_t;

/**
 * @brief Inicializa o filtro digital.
 *
 * @param[out] filter Ponteiro para estrutura do filtro.
 * @param[in] alpha Coeficiente de suavização.
 * @return ESP_OK Inicialização bem-sucedida.
 * @return ESP_ERR_INVALID_ARG Ponteiro nulo.
 */
esp_err_t filter_init(filter_t *filter, float alpha);

/**
 * @brief Atualiza o filtro com uma nova amostra.
 *
 * @param[in,out] filter Ponteiro para estrutura do filtro.
 * @param[in] sample Nova amostra.
 * @param[out] filtered_value Ponteiro para receber o valor filtrado.
 * @return ESP_OK Atualização realizada.
 * @return ESP_ERR_INVALID_ARG Ponteiro nulo.
 */
esp_err_t filter_update(filter_t *filter, float sample, float *filtered_value);

/**
 * @brief Reseta o filtro para um valor inicial.
 *
 * @param[in,out] filter Ponteiro para estrutura do filtro.
 * @param[in] initial_value Valor inicial.
 * @return ESP_OK Reset realizado.
 * @return ESP_ERR_INVALID_ARG Ponteiro nulo.
 */
esp_err_t filter_reset(filter_t *filter, float initial_value);
