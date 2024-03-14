#ifndef ESP32Domotic_h
#define ESP32Domotic_h

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

class ESP32Domotic {

    public:
        ESP32Domotic();
        ~ESP32Domotic();

        void init();
        void loop();
};

#endif