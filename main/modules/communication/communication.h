#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file communication.h
 * @brief Interface para comunicação externa do sistema de controle térmico.
 *
 * Fornece funções para inicialização, controle e obtenção de status via interface de comunicação.
 */

#pragma once

#include "modules/common/types.h"

#include "esp_err.h"

/**
 * @brief Inicializa o módulo de comunicação.
 *
 * Deve ser chamada uma vez antes de utilizar qualquer outra função de comunicação.
 *
 * @return ESP_OK Inicialização bem-sucedida.
 * @return ESP_FAIL Falha na inicialização do hardware ou recursos.
 */
esp_err_t communication_init(void);

/**
 * @brief Inicia a task de comunicação responsável pelo processamento assíncrono.
 *
 * Cria e inicia a task FreeRTOS para lidar com a comunicação externa.
 *
 * @return ESP_OK Task criada e iniciada com sucesso.
 * @return ESP_ERR_INVALID_STATE Task já estava em execução.
 * @return ESP_FAIL Falha ao criar a task.
 */
esp_err_t communication_task_start(void);

/**
 * @brief Obtém o status térmico atual do sistema.
 *
 * Preenche a estrutura informada com os dados mais recentes do controle térmico.
 *
 * @param[out] status Ponteiro para estrutura que receberá o status.
 *
 * @return ESP_OK Status obtido com sucesso.
 * @return ESP_ERR_INVALID_ARG Ponteiro status é nulo.
 * @return ESP_FAIL Falha ao acessar os dados de status.
 */
esp_err_t communication_get_status(thermal_status_t *status);

/**
 * @brief Define um novo setpoint de temperatura para o sistema.
 *
 * Atualiza o valor de referência de temperatura a ser controlado.
 *
 * @param[in] setpoint_c Novo setpoint em graus Celsius.
 *
 * @return ESP_OK Setpoint atualizado com sucesso.
 * @return ESP_ERR_INVALID_ARG Valor de setpoint fora dos limites permitidos.
 * @return ESP_FAIL Falha ao atualizar o setpoint.
 */
esp_err_t communication_set_setpoint(float setpoint_c);

#ifdef __cplusplus
}
#endif
