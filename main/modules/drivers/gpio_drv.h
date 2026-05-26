#pragma once

#include "esp_err.h"

#include <stdbool.h>

/**
 * @brief Inicializa o driver de GPIO.
 *
 * @return ESP_OK Inicialização bem-sucedida.
 * @return ESP_FAIL Falha na inicialização.
 */
esp_err_t gpio_drv_init(void);

/**
 * @brief Ativa ou desativa o enable via GPIO.
 *
 * @param[in] enabled true para ativar, false para desativar.
 * @return ESP_OK Operação realizada.
 * @return ESP_FAIL Falha na operação.
 */
esp_err_t gpio_drv_set_enable(bool enabled);

/**
 * @brief Ativa ou desativa o indicador de falha via GPIO.
 *
 * @param[in] active true para ativar, false para desativar.
 * @return ESP_OK Operação realizada.
 * @return ESP_FAIL Falha na operação.
 */
esp_err_t gpio_drv_set_fault_indicator(bool active);
