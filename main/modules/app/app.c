#include "app.h"

#include "modules/app/app_state_machine.h"
#include "modules/thermal/thermal.h"

esp_err_t app_init(void)
{
    esp_err_t ret = app_state_machine_init();
    if (ret != ESP_OK) {
        return ret;
    }

    return thermal_init();
}
