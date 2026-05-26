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

#include "modules/common/types.h"

#include "esp_err.h"

/**
 * @brief Inicializa a máquina de estados da aplicação.
 *
 * @return ESP_OK Inicialização bem-sucedida.
 * @return ESP_FAIL Falha na inicialização.
 */
esp_err_t app_state_machine_init(void);

/**
 * @brief Obtém o estado atual da aplicação.
 *
 * @param[out] state Ponteiro para receber o estado atual.
 * @return ESP_OK Estado obtido com sucesso.
 * @return ESP_ERR_INVALID_ARG Ponteiro nulo.
 */
esp_err_t app_state_machine_get_state(app_state_t *state);

/**
 * @brief Define o estado da aplicação.
 *
 * @param[in] state Novo estado a ser definido.
 * @return ESP_OK Estado atualizado.
 * @return ESP_ERR_INVALID_ARG Valor inválido.
 */
esp_err_t app_state_machine_set_state(app_state_t state);

/**
 * @brief Atualiza o estado da aplicação a partir do estado de segurança.
 *
 * @param[in] safety_state Estado de segurança atual.
 * @return ESP_OK Atualização realizada.
 * @return ESP_ERR_INVALID_ARG Valor inválido.
 */
esp_err_t app_state_machine_update_from_safety(safety_state_t safety_state);
