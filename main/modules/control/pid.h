#pragma once

#include "esp_err.h"

#include <stdbool.h>

/**
 * @brief Estrutura do controlador PID.
 *
 * Armazena parâmetros, estados internos e limites do controle PID.
 */
typedef struct {
    float kp;                /**< Ganho proporcional. */
    float ki;                /**< Ganho integral. */
    float kd;                /**< Ganho derivativo. */
    float output_min;        /**< Saída mínima permitida. */
    float output_max;        /**< Saída máxima permitida. */
    float integral;          /**< Acumulador do termo integral. */
    float previous_error;    /**< Erro anterior para cálculo do termo derivativo. */
    bool has_previous_error; /**< Indica se previous_error já foi inicializado. */
} pid_controller_t;

/**
 * @brief Inicializa o controlador PID.
 *
 * @param[out] pid Ponteiro para estrutura PID a ser inicializada.
 * @param[in] kp Ganho proporcional.
 * @param[in] ki Ganho integral.
 * @param[in] kd Ganho derivativo.
 * @param[in] output_min Saída mínima.
 * @param[in] output_max Saída máxima.
 * @return ESP_OK Inicialização bem-sucedida.
 * @return ESP_ERR_INVALID_ARG Ponteiro nulo.
 */
esp_err_t pid_init(pid_controller_t *pid, float kp, float ki, float kd,
                   float output_min, float output_max);

/**
 * @brief Reseta o controlador PID.
 *
 * @param[in,out] pid Ponteiro para estrutura PID a ser resetada.
 * @return ESP_OK Reset realizado.
 * @return ESP_ERR_INVALID_ARG Ponteiro nulo.
 */
esp_err_t pid_reset(pid_controller_t *pid);

/**
 * @brief Atualiza o controlador PID e calcula a nova saída.
 *
 * @param[in,out] pid Ponteiro para estrutura PID.
 * @param[in] setpoint Valor de referência.
 * @param[in] measurement Valor medido.
 * @param[in] period_s Período de amostragem (s).
 * @param[out] output Ponteiro para receber a saída calculada.
 * @return ESP_OK Atualização realizada.
 * @return ESP_ERR_INVALID_ARG Ponteiro nulo.
 */
esp_err_t pid_update(pid_controller_t *pid, float setpoint, float measurement,
                     float period_s, float *output);
