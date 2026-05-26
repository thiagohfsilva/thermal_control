#pragma once

#include "esp_err.h"

/**
 * @brief Inicializa o driver ADC.
 *
 * @return ESP_OK Inicialização bem-sucedida.
 * @return ESP_FAIL Falha na inicialização.
 */
esp_err_t adc_drv_init(void);

/**
 * @brief Lê o valor bruto do ADC.
 *
 * @param[out] raw_value Ponteiro para receber o valor lido.
 * @return ESP_OK Valor lido.
 * @return ESP_ERR_INVALID_ARG Ponteiro nulo.
 * @return ESP_FAIL Falha na leitura.
 */
esp_err_t adc_drv_read_raw(int *raw_value);
