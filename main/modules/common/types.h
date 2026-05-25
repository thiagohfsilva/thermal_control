#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    APP_STATE_INIT = 0,
    APP_STATE_RUNNING,
    APP_STATE_FAULT,
    APP_STATE_SHUTDOWN,
} app_state_t;

typedef enum {
    SAFETY_STATE_OK = 0,
    SAFETY_STATE_SENSOR_ERROR,
    SAFETY_STATE_OVERTEMPERATURE,
    SAFETY_STATE_UNDERTEMPERATURE,
} safety_state_t;

typedef struct {
    float temperature_c;
    float filtered_temperature_c;
    float setpoint_c;
    float duty_percent;
    app_state_t app_state;
    safety_state_t safety_state;
    bool sensor_valid;
} thermal_status_t;
