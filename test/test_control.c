#include "unity.h"

#include "main/modules/control/pid.h"

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
