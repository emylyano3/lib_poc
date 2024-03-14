#include "ESP32Domotic.h"

WiFiClient      _wifiClient;
PubSubClient    _mqttClient(_wifiClient);

ESP32Domotic::ESP32Domotic(){}
ESP32Domotic::~ESP32Domotic(){}

void ESP32Domotic::init() {
    _mqttClient.connect("lib_poc_test");
}

void ESP32Domotic::loop() {
}