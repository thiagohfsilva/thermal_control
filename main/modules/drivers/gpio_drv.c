#include "gpio_drv.h"

#include "esp_err.h"

esp_err_t gpio_drv_init(void)
{
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t gpio_drv_set_enable(bool enabled)
{
    (void)enabled;
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t gpio_drv_set_fault_indicator(bool active)
{
    (void)active;
    return ESP_ERR_NOT_SUPPORTED;
}
