#include "unity.h"

#include "main/modules/control/filter.h"
#include "main/modules/control/pid.h"
#include "main/modules/sensors/ntc_sensor.h"

void test_pid_initializes_and_updates_output(void)
{
    pid_controller_t pid;
    float output = 0.0f;

    TEST_ASSERT_EQUAL(
        ESP_OK, pid_init(&pid, 1.0f, 0.0f, 0.0f, 0.0f, 100.0f));
    TEST_ASSERT_EQUAL(
        ESP_OK, pid_update(&pid, 50.0f, 40.0f, 0.1f, &output));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 10.0f, output);
}

void test_pid_saturates_output_limits(void)
{
    pid_controller_t pid;
    float output = 0.0f;

    TEST_ASSERT_EQUAL(
        ESP_OK, pid_init(&pid, 100.0f, 0.0f, 0.0f, 0.0f, 100.0f));
    TEST_ASSERT_EQUAL(
        ESP_OK, pid_update(&pid, 100.0f, 0.0f, 0.1f, &output));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 100.0f, output);

    TEST_ASSERT_EQUAL(
        ESP_OK, pid_update(&pid, 0.0f, 100.0f, 0.1f, &output));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, output);
}

void test_pid_anti_windup_recovers_after_saturation(void)
{
    pid_controller_t pid;
    float output = 0.0f;

    TEST_ASSERT_EQUAL(
        ESP_OK, pid_init(&pid, 10.0f, 10.0f, 0.0f, 0.0f, 100.0f));

    for (int i = 0; i < 20; i++) {
        TEST_ASSERT_EQUAL(
            ESP_OK, pid_update(&pid, 100.0f, 0.0f, 0.1f, &output));
    }

    TEST_ASSERT_EQUAL(
        ESP_OK, pid_update(&pid, 0.0f, 0.0f, 0.1f, &output));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, output);
}

void test_filter_smooths_temperature_sample(void)
{
    filter_t filter;
    float filtered = 0.0f;

    TEST_ASSERT_EQUAL(ESP_OK, filter_init(&filter, 0.5f));
    TEST_ASSERT_EQUAL(ESP_OK, filter_update(&filter, 10.0f, &filtered));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 10.0f, filtered);
    TEST_ASSERT_EQUAL(ESP_OK, filter_update(&filter, 20.0f, &filtered));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 15.0f, filtered);
}

void test_filter_reset_sets_known_value(void)
{
    filter_t filter;
    float filtered = 0.0f;

    TEST_ASSERT_EQUAL(ESP_OK, filter_init(&filter, 0.5f));
    TEST_ASSERT_EQUAL(ESP_OK, filter_update(&filter, 50.0f, &filtered));
    TEST_ASSERT_EQUAL(ESP_OK, filter_reset(&filter, 25.0f));
    TEST_ASSERT_EQUAL(ESP_OK, filter_update(&filter, 25.0f, &filtered));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 25.0f, filtered);
}

void test_ntc_nominal_resistance_converts_to_25c(void)
{
    float temperature_c = 0.0f;

    TEST_ASSERT_EQUAL(
        ESP_OK, ntc_sensor_convert_resistance(10000.0f, &temperature_c));
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.0f, temperature_c);
}

void test_ntc_rejects_invalid_raw_readings(void)
{
    float temperature_c = 0.0f;

    TEST_ASSERT_EQUAL(
        ESP_ERR_INVALID_RESPONSE,
        ntc_sensor_convert_raw(0, &temperature_c));
    TEST_ASSERT_EQUAL(
        ESP_ERR_INVALID_RESPONSE,
        ntc_sensor_convert_raw(4095, &temperature_c));
}
