#pragma once

#include "driver/adc_types_legacy.h"
#include "driver/gpio.h"
#include "driver/ledc.h"

#define THERMAL_NTC_ADC_UNIT ADC_UNIT_1
#define THERMAL_NTC_ADC_CHANNEL ADC_CHANNEL_0
#define THERMAL_NTC_ADC_ATTEN ADC_ATTEN_DB_12
#define THERMAL_NTC_ADC_BITWIDTH ADC_BITWIDTH_DEFAULT

#define THERMAL_PWM_GPIO GPIO_NUM_4

#define THERMAL_DEFAULT_SETPOINT_C (37.0f)
