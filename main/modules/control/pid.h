#pragma once

#include "esp_err.h"

#include <stdbool.h>

typedef struct {
    float kp;
    float ki;
    float kd;
    float output_min;
    float output_max;
    float integral;
    float previous_error;
    bool has_previous_error;
} pid_controller_t;

esp_err_t pid_init(
    pid_controller_t *pid,
    float kp,
    float ki,
    float kd,
    float output_min,
    float output_max);
esp_err_t pid_reset(pid_controller_t *pid);
esp_err_t pid_update(
    pid_controller_t *pid,
    float setpoint,
    float measurement,
    float period_s,
    float *output);
