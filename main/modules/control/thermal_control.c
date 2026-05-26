#include "thermal_control.h"

#include "modules/common/defines.h"
#include "modules/control/pid.h"
#include "esp_log.h"

#include "esp_err.h"

static pid_controller_t s_pid;
static const char *TAG = "THERMAL_CTRL";

esp_err_t thermal_control_init(void)
{
    ESP_LOGI(TAG, "Initializing PID controller");
    return pid_init(&s_pid, 8.0f, 0.2f, 0.0f, THERMAL_PERCENT_MIN,
                    THERMAL_PERCENT_MAX);
}

esp_err_t thermal_control_reset(void)
{
    ESP_LOGI(TAG, "Resetting PID controller");
    return pid_reset(&s_pid);
}

esp_err_t thermal_control_update(float setpoint_c, float temperature_c,
                                 float period_s, float *duty_percent)
{
    ESP_LOGI(TAG, "PID update: setpoint=%.2f, temp=%.2f, period=%.2fs", setpoint_c, temperature_c, period_s);
    if (duty_percent == NULL) {
        ESP_LOGE(TAG, "duty_percent pointer is NULL");
        return ESP_ERR_INVALID_ARG;
    }

    esp_err_t ret =
        pid_update(&s_pid, setpoint_c, temperature_c, period_s, duty_percent);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "PID update failed");
        return ret;
    }

    if (*duty_percent < THERMAL_PERCENT_MIN) {
        ESP_LOGW(TAG, "Duty below min, clamping to %.2f", THERMAL_PERCENT_MIN);
        *duty_percent = THERMAL_PERCENT_MIN;
    }

    if (*duty_percent > THERMAL_PERCENT_MAX) {
        ESP_LOGW(TAG, "Duty above max, clamping to %.2f", THERMAL_PERCENT_MAX);
        *duty_percent = THERMAL_PERCENT_MAX;
    }

    ESP_LOGI(TAG, "PID output duty: %.2f%%", *duty_percent);
    return ESP_OK;
}
