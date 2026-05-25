#pragma once

#include "esp_err.h"

#include <stdbool.h>

typedef struct {
    float alpha;
    float value;
    bool initialized;
} filter_t;

esp_err_t filter_init(filter_t *filter, float alpha);
esp_err_t filter_update(filter_t *filter, float sample, float *filtered_value);
esp_err_t filter_reset(filter_t *filter, float initial_value);
