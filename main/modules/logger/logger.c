#include "logger.h"

#include "esp_err.h"

#include <stdbool.h>

static bool s_initialized;

esp_err_t logger_init(void)
{
    if (s_initialized) {
        return ESP_OK;
    }

    esp_err_t ret = logger_task_start();
    if (ret != ESP_OK) {
        return ret;
    }

    s_initialized = true;
    return ESP_OK;
}
