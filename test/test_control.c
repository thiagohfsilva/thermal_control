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
