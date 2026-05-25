#include "communication.h"

#include "modules/common/config.h"

#include "esp_err.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <stdbool.h>

static void communication_task(void *arg)
{
    (void)arg;

    while (true) {
        vTaskDelay(pdMS_TO_TICKS(THERMAL_LOG_PERIOD_MS));
    }
}

esp_err_t communication_task_start(void)
{
    BaseType_t result = xTaskCreate(communication_task, "communication",
                                    COMMUNICATION_TASK_STACK_SIZE, NULL,
                                    COMMUNICATION_TASK_PRIORITY, NULL);

    return result == pdPASS ? ESP_OK : ESP_ERR_NO_MEM;
}
