#include "ESP32Config.h"

ESP32Config::ESP32Config(){}
ESP32Config::~ESP32Config(){}

bool ESP32Config::connectWifiNetwork(bool existConfig){return true;}
bool ESP32Config::startConfigPortal(){return true;}

/* setup methods */
/* Set wifi connect timeout in millis */
void ESP32Config::setWifiConnectTimeout(unsigned long seconds){}
void ESP32Config::setConfigPortalTimeout(unsigned long seconds){}
void ESP32Config::setPortalSSID(const char *apName){}
void ESP32Config::setPortalPassword(const char *apPass){}
bool ESP32Config::addParameter(ConfigParam *p){return true;}
void ESP32Config::setFeedbackPin(uint8_t pin){}
void ESP32Config::setAPStaticIP(IPAddress ip, IPAddress gw, IPAddress sn){}

// Returns the param under the specified index
ConfigParam* ESP32Config::getParameter(uint8_t index){return NULL;}

// Returns the numer of params existing
uint8_t ESP32Config::getParamsCount(){return 1;}

//called when AP mode and config portal is started
void ESP32Config::setAPCallback (std::function<void(ESP32Config*)> callback){}

//called when connecting station to AP
void ESP32Config::setStationNameCallback (std::function<const char*(void)> callback){}

//called when settings have been changed and connection was successful
void ESP32Config::setSaveConfigCallback (std::function<void(void)> callback){}

//defaults to not showing anything under 8% signal quality if called
void ESP32Config::setMinimumSignalQuality (int quality){}

// Blocking signal feedback. Turns on/off a signal a specific times waiting a step time for each state flip.
void ESP32Config::blockingFeedback (uint8_t pin, long stepTime, uint8_t times){}

// Non blocking signal feedback (to be used inside a loop). Uses global variables to control when to flip the signal state according to the step time.
void ESP32Config::nonBlockingFeedback (uint8_t pin, int stepTime){}

void ESP32Config::handleWifi(bool scan) {}
void ESP32Config::handleWifiSave() {}
void ESP32Config::handleNotFound() {}
bool ESP32Config::captivePortal() {return true;}
bool ESP32Config::configPortalHasTimeout() {return true;}
bool ESP32Config::isIp(String str) {return true;}
String ESP32Config::toStringIp(IPAddress ip) {return "";}
int ESP32Config::getRSSIasQuality(int RSSI) {return 1;}