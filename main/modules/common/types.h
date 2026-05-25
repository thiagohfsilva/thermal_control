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
