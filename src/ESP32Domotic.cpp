#include "ESP32Domotic.h"

void ESP32Domotic::init() {
    _mqttClient.connect("lib_poc_test");
}

void ESP32Domotic::loop() {
}