#include "ModuleConfig.h"

ModuleConfig::ModuleConfig(){}
ModuleConfig::~ModuleConfig(){}

bool ModuleConfig::connectWifiNetwork(bool existConfig){return true;}
bool ModuleConfig::startConfigPortal(){return true;}

/* setup methods */
/* Set wifi connect timeout in millis */
void ModuleConfig::setWifiConnectTimeout(unsigned long seconds){}
void ModuleConfig::setConfigPortalTimeout(unsigned long seconds){}
void ModuleConfig::setPortalSSID(const char *apName){}
void ModuleConfig::setPortalPassword(const char *apPass){}
bool ModuleConfig::addParameter(ConfigParam *p){return true;}
void ModuleConfig::setFeedbackPin(uint8_t pin){}
void ModuleConfig::setAPStaticIP(IPAddress ip, IPAddress gw, IPAddress sn){}

// Returns the param under the specified index
ConfigParam* ModuleConfig::getParameter(uint8_t index){return NULL;}

// Returns the numer of params existing
uint8_t ModuleConfig::getParamsCount(){return 1;}

//called when AP mode and config portal is started
void ModuleConfig::setAPCallback (std::function<void(ModuleConfig*)> callback){}

//called when connecting station to AP
void ModuleConfig::setStationNameCallback (std::function<const char*(void)> callback){}

//called when settings have been changed and connection was successful
void ModuleConfig::setSaveConfigCallback (std::function<void(void)> callback){}

//defaults to not showing anything under 8% signal quality if called
void ModuleConfig::setMinimumSignalQuality (int quality){}

// Blocking signal feedback. Turns on/off a signal a specific times waiting a step time for each state flip.
void ModuleConfig::blockingFeedback (uint8_t pin, long stepTime, uint8_t times){}

// Non blocking signal feedback (to be used inside a loop). Uses global variables to control when to flip the signal state according to the step time.
void ModuleConfig::nonBlockingFeedback (uint8_t pin, int stepTime){}

void ModuleConfig::handleWifi(bool scan) {}
void ModuleConfig::handleWifiSave() {}
void ModuleConfig::handleNotFound() {}
bool ModuleConfig::captivePortal() {return true;}
bool ModuleConfig::configPortalHasTimeout() {return true;}
bool ModuleConfig::isIp(String str) {return true;}
String ModuleConfig::toStringIp(IPAddress ip) {return "";}
int ModuleConfig::getRSSIasQuality(int RSSI) {return 1;}