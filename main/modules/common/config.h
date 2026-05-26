/*
 * Copyright (C) 2026 Thiago Henrique Ferreira da Silva
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Author: Thiago Henrique Ferreira da Silva
 */
/**
 * @file config.h
 * @brief Definições de configuração do sistema de controle térmico.
 */
#pragma once

#include "driver/adc_types_legacy.h"
#include "driver/gpio.h"
#include "driver/ledc.h"

#define THERMAL_NTC_ADC_UNIT ADC_UNIT_1
#define THERMAL_NTC_ADC_CHANNEL ADC_CHANNEL_0
#define THERMAL_NTC_ADC_ATTEN ADC_ATTEN_DB_12
#define THERMAL_NTC_ADC_BITWIDTH ADC_BITWIDTH_DEFAULT
#define THERMAL_NTC_ADC_MAX_RAW (4095.0f)
#define THERMAL_NTC_ADC_REFERENCE_VOLTAGE (3.3f)

#define THERMAL_PWM_GPIO GPIO_NUM_4
#define THERMAL_PWM_TIMER LEDC_TIMER_0
#define THERMAL_PWM_MODE LEDC_LOW_SPEED_MODE
#define THERMAL_PWM_CHANNEL LEDC_CHANNEL_0
#define THERMAL_PWM_DUTY_RES LEDC_TIMER_10_BIT
#define THERMAL_PWM_FREQUENCY_HZ (1000U)
#define THERMAL_ENABLE_GPIO GPIO_NUM_NC
#define THERMAL_FAULT_GPIO GPIO_NUM_NC

#define THERMAL_CONTROL_PERIOD_MS (100U)

#define THERMAL_MIN_SAFE_TEMPERATURE_C (-10.0f)
#define THERMAL_MAX_SAFE_TEMPERATURE_C (90.0f)
#define THERMAL_MIN_SETPOINT_C (0.0f)
#define THERMAL_MAX_SETPOINT_C (80.0f)
#define THERMAL_DEFAULT_SETPOINT_C (37.0f)

#define THERMAL_NTC_NOMINAL_RESISTANCE_OHM (10000.0f)
#define THERMAL_NTC_SERIES_RESISTOR_OHM (10000.0f)
#define THERMAL_NTC_BETA_COEFFICIENT (3950.0f)
#define THERMAL_NTC_NOMINAL_TEMPERATURE_C (25.0f)

#define THERMAL_LOG_PERIOD_MS (1000U)
#define THERMAL_TASK_STACK_SIZE (4096U)
#define THERMAL_TASK_PRIORITY (5U)
#define LOGGER_TASK_STACK_SIZE (3072U)
#define LOGGER_TASK_PRIORITY (2U)
#define COMMUNICATION_TASK_STACK_SIZE (3072U)
#define COMMUNICATION_TASK_PRIORITY (2U)
