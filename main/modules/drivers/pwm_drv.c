#include "pwm_drv.h"

#include "esp_err.h"

esp_err_t pwm_drv_init(void)
{
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t pwm_drv_set_duty(float duty_percent)
{
    (void)duty_percent;
    return ESP_ERR_NOT_SUPPORTED;
}
