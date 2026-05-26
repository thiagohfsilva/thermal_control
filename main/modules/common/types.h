/**
 * @file types.h
 * @brief Tipos e estruturas comuns do sistema de controle térmico.
 */
#pragma once

#include <stdbool.h>
#include <stdint.h>


/**
 * @brief Estados possíveis da aplicação.
 */
typedef enum {
    APP_STATE_INIT = 0,    /**< Inicialização do sistema. */
    APP_STATE_RUNNING,     /**< Sistema em operação normal. */
    APP_STATE_FAULT,       /**< Falha detectada. */
    APP_STATE_SHUTDOWN,    /**< Sistema desligado. */
} app_state_t;


/**
 * @brief Estados de segurança térmica.
 */
typedef enum {
    SAFETY_STATE_OK = 0,           /**< Operação segura. */
    SAFETY_STATE_SENSOR_ERROR,     /**< Erro no sensor de temperatura. */
    SAFETY_STATE_OVERTEMPERATURE,  /**< Temperatura acima do limite. */
    SAFETY_STATE_UNDERTEMPERATURE, /**< Temperatura abaixo do limite. */
} safety_state_t;


/**
 * @brief Estrutura de status térmico do sistema.
 *
 * Armazena medições, setpoint, duty, estados e validade do sensor.
 */
typedef struct {
    float temperature_c;           /**< Temperatura medida (°C). */
    float filtered_temperature_c;  /**< Temperatura filtrada (°C). */
    float setpoint_c;              /**< Setpoint de temperatura (°C). */
    float duty_percent;            /**< Duty cycle aplicado (%). */
    app_state_t app_state;         /**< Estado atual da aplicação. */
    safety_state_t safety_state;   /**< Estado de segurança térmica. */
    bool sensor_valid;             /**< true se o sensor está válido. */
} thermal_status_t;
