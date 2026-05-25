#include "communication.h"

#include "esp_err.h"

#include <stdbool.h>

static bool s_initialized;

esp_err_t communication_init(void)
{
    if (s_initialized) {
        return ESP_OK;
    }

    s_initialized = true;
    return ESP_OK;
}

esp_err_t communication_get_status(thermal_status_t *status)
{
    (void)status;
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t communication_set_setpoint(float setpoint_c)
{
    (void)setpoint_c;
    return ESP_ERR_NOT_SUPPORTED;
}
