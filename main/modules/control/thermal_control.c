#include "thermal_control.h"

#include "modules/common/defines.h"
#include "modules/control/pid.h"

#include "esp_err.h"

static pid_controller_t s_pid;

esp_err_t thermal_control_init(void)
{
    return pid_init(
        &s_pid,
        8.0f,
        0.2f,
        0.0f,
        THERMAL_PERCENT_MIN,
        THERMAL_PERCENT_MAX);
}

esp_err_t thermal_control_reset(void)
{
    return pid_reset(&s_pid);
}

esp_err_t thermal_control_update(
    float setpoint_c,
    float temperature_c,
    float period_s,
    float *duty_percent)
{
    if (duty_percent == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    return pid_update(
        &s_pid, setpoint_c, temperature_c, period_s, duty_percent);
}
