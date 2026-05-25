#include "pid.h"

#include "esp_err.h"

esp_err_t pid_init(
    pid_controller_t *pid,
    float kp,
    float ki,
    float kd,
    float output_min,
    float output_max)
{
    if (pid == NULL || output_max < output_min) {
        return ESP_ERR_INVALID_ARG;
    }

    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->output_min = output_min;
    pid->output_max = output_max;

    return pid_reset(pid);
}

esp_err_t pid_reset(pid_controller_t *pid)
{
    if (pid == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    pid->integral = 0.0f;
    pid->previous_error = 0.0f;
    pid->has_previous_error = false;

    return ESP_OK;
}

esp_err_t pid_update(
    pid_controller_t *pid,
    float setpoint,
    float measurement,
    float period_s,
    float *output)
{
    if (pid == NULL || output == NULL || period_s <= 0.0f) {
        return ESP_ERR_INVALID_ARG;
    }

    *output = 0.0f;
    return ESP_ERR_NOT_SUPPORTED;
}
