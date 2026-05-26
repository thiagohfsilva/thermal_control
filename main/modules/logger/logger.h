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
