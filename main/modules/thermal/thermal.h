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
