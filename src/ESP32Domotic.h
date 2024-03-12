#ifndef ESP32_DOMOTIC_H
#define ESP32_DOMOTIC_H

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient      _wifiClient;
PubSubClient    _mqttClient(_wifiClient);

class ESP32Domotic {

    public:
        void init();
        void loop();
};

#endif