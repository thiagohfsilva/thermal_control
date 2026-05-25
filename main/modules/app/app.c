#include "app.h"

#include "modules/app/app_state_machine.h"
#include "modules/communication/communication.h"
#include "modules/logger/logger.h"
#include "modules/thermal/thermal.h"

esp_err_t app_init(void)
{
    esp_err_t ret = app_state_machine_init();
    if (ret != ESP_OK) {
        return ret;
    }

    ret = logger_init();
    if (ret != ESP_OK) {
        (void)app_state_machine_set_state(APP_STATE_FAULT);
        return ret;
    }

    ret = communication_init();
    if (ret != ESP_OK) {
        (void)app_state_machine_set_state(APP_STATE_FAULT);
        return ret;
    }

    ret = thermal_init();
    if (ret != ESP_OK) {
        (void)app_state_machine_set_state(APP_STATE_FAULT);
        return ret;
    }

    return app_state_machine_set_state(APP_STATE_RUNNING);
}
