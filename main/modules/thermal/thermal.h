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
 * @brief Inicializa o módulo térmico.
 *
 * @return ESP_OK Inicialização bem-sucedida.
 * @return ESP_FAIL Falha na inicialização.
 */
esp_err_t thermal_init(void);

/**
 * @brief Obtém o status térmico atual.
 *
 * @param[out] status Ponteiro para receber o status.
 * @return ESP_OK Status obtido.
 * @return ESP_ERR_INVALID_ARG Ponteiro nulo.
 */
esp_err_t thermal_get_status(thermal_status_t *status);

/**
 * @brief Define o setpoint de temperatura.
 *
 * @param[in] setpoint_c Novo setpoint (°C).
 * @return ESP_OK Setpoint atualizado.
 * @return ESP_ERR_INVALID_ARG Valor inválido.
 */
esp_err_t thermal_set_setpoint(float setpoint_c);

/**
 * @brief Executa um ciclo de controle térmico.
 *
 * @return ESP_OK Ciclo executado.
 * @return ESP_FAIL Falha na execução.
 */
esp_err_t thermal_execute_cycle(void);

/**
 * @brief Inicia a task de controle térmico.
 *
 * @return ESP_OK Task iniciada.
 * @return ESP_ERR_INVALID_STATE Task já estava em execução.
 * @return ESP_FAIL Falha ao criar a task.
 */
esp_err_t thermal_task_start(void);
