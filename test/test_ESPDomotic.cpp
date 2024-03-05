#include <unity.h>
#include "ESP32Config.h"

void test_init() {
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_init);
    UNITY_END();
}

void loop() {
    // no-op
}
