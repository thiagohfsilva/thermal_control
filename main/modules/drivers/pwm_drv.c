#include "pwm_drv.h"

#include "modules/common/config.h"

#include "driver/ledc.h"
#include "esp_err.h"

esp_err_t pwm_drv_init(void)
{
    ledc_timer_config_t timer_config = {
        .speed_mode = THERMAL_PWM_MODE,
        .duty_resolution = THERMAL_PWM_DUTY_RES,
        .timer_num = THERMAL_PWM_TIMER,
        .freq_hz = THERMAL_PWM_FREQUENCY_HZ,
        .clk_cfg = LEDC_AUTO_CLK,
    };

    esp_err_t ret = ledc_timer_config(&timer_config);
    if (ret != ESP_OK) {
        return ret;
    }

    ledc_channel_config_t channel_config = {
        .gpio_num = THERMAL_PWM_GPIO,
        .speed_mode = THERMAL_PWM_MODE,
        .channel = THERMAL_PWM_CHANNEL,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = THERMAL_PWM_TIMER,
        .duty = 0,
        .hpoint = 0,
    };

    ret = ledc_channel_config(&channel_config);
    if (ret != ESP_OK) {
        return ret;
    }

    return pwm_drv_set_duty(0.0f);
}

esp_err_t pwm_drv_set_duty(float duty_percent)
{
    const uint32_t max_duty = (1U << THERMAL_PWM_DUTY_RES) - 1U;
    const uint32_t duty = (uint32_t)((duty_percent / 100.0f) * max_duty);

    esp_err_t ret = ledc_set_duty(
        THERMAL_PWM_MODE, THERMAL_PWM_CHANNEL, duty);
    if (ret != ESP_OK) {
        return ret;
    }

    return ledc_update_duty(THERMAL_PWM_MODE, THERMAL_PWM_CHANNEL);
}
