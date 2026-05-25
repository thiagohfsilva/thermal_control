#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    APP_STATE_INIT = 0,
    APP_STATE_RUNNING,
    APP_STATE_FAULT,
    APP_STATE_SHUTDOWN,
} app_state_t;
