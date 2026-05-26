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
#include "pid.h"

#include "esp_err.h"

esp_err_t pid_init(pid_controller_t *pid, float kp, float ki, float kd,
                   float output_min, float output_max)
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

esp_err_t pid_update(pid_controller_t *pid, float setpoint, float measurement,
                     float period_s, float *output)
{
    if (pid == NULL || output == NULL || period_s <= 0.0f) {
        return ESP_ERR_INVALID_ARG;
    }

    const float error = setpoint - measurement;
    const float candidate_integral = pid->integral + (error * period_s);

    float derivative = 0.0f;
    if (pid->has_previous_error) {
        derivative = (error - pid->previous_error) / period_s;
    }

    float calculated_output = (pid->kp * error) +
                              (pid->ki * candidate_integral) +
                              (pid->kd * derivative);

    if (calculated_output < pid->output_min) {
        calculated_output = pid->output_min;
    } else if (calculated_output > pid->output_max) {
        calculated_output = pid->output_max;
    } else {
        pid->integral = candidate_integral;
    }

    pid->previous_error = error;
    pid->has_previous_error = true;
    *output = calculated_output;

    return ESP_OK;
}
