#include "app_state_machine.h"

#include "esp_err.h"

static app_state_t s_app_state = APP_STATE_INIT;

esp_err_t app_state_machine_init(void)
{
    s_app_state = APP_STATE_INIT;
    return ESP_OK;
}

esp_err_t app_state_machine_get_state(app_state_t *state)
{
    if (state == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    *state = s_app_state;
    return ESP_OK;
}

esp_err_t app_state_machine_set_state(app_state_t state)
{
    if (s_app_state == APP_STATE_SHUTDOWN) {
        return ESP_ERR_INVALID_STATE;
    }

    if (s_app_state == APP_STATE_FAULT && state == APP_STATE_RUNNING) {
        return ESP_ERR_INVALID_STATE;
    }

    s_app_state = state;
    return ESP_OK;
}

esp_err_t app_state_machine_update_from_safety(safety_state_t safety_state)
{
    if (safety_state != SAFETY_STATE_OK) {
        s_app_state = APP_STATE_FAULT;
    }

    return ESP_OK;
}
