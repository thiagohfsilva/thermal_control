#include "filter.h"

#include "esp_err.h"

esp_err_t filter_init(filter_t *filter, float alpha)
{
    if (filter == NULL || alpha <= 0.0f || alpha > 1.0f) {
        return ESP_ERR_INVALID_ARG;
    }

    filter->alpha = alpha;
    filter->value = 0.0f;
    filter->initialized = false;

    return ESP_OK;
}

esp_err_t filter_update(filter_t *filter, float sample, float *filtered_value)
{
    if (filter == NULL || filtered_value == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    if (!filter->initialized) {
        filter->value = sample;
        filter->initialized = true;
    } else {
        filter->value =
            (filter->alpha * sample) +
            ((1.0f - filter->alpha) * filter->value);
    }

    *filtered_value = filter->value;
    return ESP_OK;
}

esp_err_t filter_reset(filter_t *filter, float initial_value)
{
    if (filter == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    filter->value = initial_value;
    filter->initialized = true;

    return ESP_OK;
}
