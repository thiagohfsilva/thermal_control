#pragma once

#include "esp_err.h"

/**
 * @brief Inicializa o driver PWM.
 *
 * @return ESP_OK Inicialização bem-sucedida.
 * @return ESP_FAIL Falha na inicialização.
 */
esp_err_t pwm_drv_init(void);

/**
 * @brief Define o duty cycle do PWM.
 *
 * @param[in] duty_percent Duty cycle em porcentagem.
 * @return ESP_OK Duty atualizado.
 * @return ESP_ERR_INVALID_ARG Valor inválido.
 * @return ESP_FAIL Falha ao atualizar duty.
 */
esp_err_t pwm_drv_set_duty(float duty_percent);
