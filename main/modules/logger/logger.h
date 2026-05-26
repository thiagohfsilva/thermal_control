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
 * @brief Inicializa o módulo de logging.
 *
 * @return ESP_OK Inicialização bem-sucedida.
 * @return ESP_FAIL Falha na inicialização.
 */
esp_err_t logger_init(void);

/**
 * @brief Inicia a task de logging.
 *
 * @return ESP_OK Task iniciada.
 * @return ESP_ERR_INVALID_STATE Task já estava em execução.
 * @return ESP_FAIL Falha ao criar a task.
 */
esp_err_t logger_task_start(void);
