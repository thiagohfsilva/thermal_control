#pragma once

#include "esp_err.h"

/**
 * @brief Inicializa o sensor NTC.
 *
 * @return ESP_OK Inicialização bem-sucedida.
 * @return ESP_FAIL Falha na inicialização.
 */
esp_err_t ntc_sensor_init(void);

/**
 * @brief Lê a temperatura do sensor NTC.
 *
 * @param[out] temperature_c Ponteiro para receber a temperatura (°C).
 * @return ESP_OK Temperatura lida.
 * @return ESP_ERR_INVALID_ARG Ponteiro nulo.
 * @return ESP_FAIL Falha na leitura.
 */
esp_err_t ntc_sensor_read_temperature(float *temperature_c);

/**
 * @brief Converte valor bruto do ADC em temperatura.
 *
 * @param[in] raw_value Valor bruto do ADC.
 * @param[out] temperature_c Ponteiro para receber a temperatura (°C).
 * @return ESP_OK Conversão realizada.
 * @return ESP_ERR_INVALID_ARG Ponteiro nulo.
 */
esp_err_t ntc_sensor_convert_raw(int raw_value, float *temperature_c);

/**
 * @brief Converte resistência em temperatura.
 *
 * @param[in] resistance_ohm Valor da resistência em ohms.
 * @param[out] temperature_c Ponteiro para receber a temperatura (°C).
 * @return ESP_OK Conversão realizada.
 * @return ESP_ERR_INVALID_ARG Ponteiro nulo.
 */
esp_err_t ntc_sensor_convert_resistance(float resistance_ohm,
                                        float *temperature_c);
