#pragma once

#include "esp_err.h"

/**
 * @brief Inicializa o módulo principal da aplicação.
 *
 * Deve ser chamada uma vez no início do sistema.
 *
 * @return ESP_OK Inicialização bem-sucedida.
 * @return ESP_FAIL Falha na inicialização.
 */
esp_err_t app_init(void);
