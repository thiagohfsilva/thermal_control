#include "communication.h"

#include "modules/thermal/thermal.h"

#include "esp_err.h"

#include <stdbool.h>

static bool s_initialized;

esp_err_t communication_init(void)
{
    if (s_initialized) {
        return ESP_OK;
    }

    esp_err_t ret = communication_task_start();
    if (ret != ESP_OK) {
        return ret;
    }

    s_initialized = true;
    return ESP_OK;
}

esp_err_t communication_get_status(thermal_status_t *status)
{
    return thermal_get_status(status);
}

esp_err_t communication_set_setpoint(float setpoint_c)
{
    return thermal_set_setpoint(setpoint_c);
}
