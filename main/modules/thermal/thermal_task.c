#include "thermal.h"

#include "modules/common/config.h"

#include "esp_err.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <stdbool.h>

static void thermal_task(void *arg)
{
    (void)arg;

    while (true) {
        (void)thermal_execute_cycle();
        vTaskDelay(pdMS_TO_TICKS(THERMAL_CONTROL_PERIOD_MS));
    }
}

esp_err_t thermal_task_start(void)
{
    BaseType_t result = xTaskCreate(
        thermal_task,
        "thermal",
        THERMAL_TASK_STACK_SIZE,
        NULL,
        THERMAL_TASK_PRIORITY,
        NULL);

    return result == pdPASS ? ESP_OK : ESP_ERR_NO_MEM;
}
