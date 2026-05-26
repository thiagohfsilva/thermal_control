#pragma once

#include "esp_err.h"

/**
 * @brief Inicializa o controle térmico.
 *
 * @return ESP_OK Inicialização bem-sucedida.
 * @return ESP_FAIL Falha na inicialização.
 */
esp_err_t thermal_control_init(void);

/**
 * @brief Reseta o controle térmico.
 *
 * @return ESP_OK Reset realizado.
 * @return ESP_FAIL Falha no reset.
 */
esp_err_t thermal_control_reset(void);

/**
 * @brief Atualiza o controle térmico e calcula o novo duty cycle.
 *
 * @param[in] setpoint_c Setpoint de temperatura (°C).
 * @param[in] temperature_c Temperatura medida (°C).
 * @param[in] period_s Período de amostragem (s).
 * @param[out] duty_percent Ponteiro para receber o duty calculado.
 * @return ESP_OK Atualização realizada.
 * @return ESP_ERR_INVALID_ARG Ponteiro nulo.
 */
esp_err_t thermal_control_update(float setpoint_c, float temperature_c,
                                 float period_s, float *duty_percent);
