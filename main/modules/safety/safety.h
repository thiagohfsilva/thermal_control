#pragma once

#include "modules/common/types.h"

#include "esp_err.h"

#include <stdbool.h>

/**
 * @brief Inicializa o módulo de segurança térmica.
 *
 * @return ESP_OK Inicialização bem-sucedida.
 * @return ESP_FAIL Falha na inicialização.
 */
esp_err_t safety_init(void);

/**
 * @brief Checa a segurança térmica com base na temperatura e validade do sensor.
 *
 * @param[in] temperature_c Temperatura medida (°C).
 * @param[in] sensor_valid Indica se o sensor está válido.
 * @param[out] state Ponteiro para receber o estado de segurança.
 * @return ESP_OK Checagem realizada.
 * @return ESP_ERR_INVALID_ARG Ponteiro nulo.
 */
esp_err_t safety_check_temperature(float temperature_c, bool sensor_valid,
                                   safety_state_t *state);

/**
 * @brief Obtém o estado de segurança atual.
 *
 * @param[out] state Ponteiro para receber o estado de segurança.
 * @return ESP_OK Estado obtido.
 * @return ESP_ERR_INVALID_ARG Ponteiro nulo.
 */
esp_err_t safety_get_state(safety_state_t *state);
