#ifndef ESP32_CONFIG_H
#define ESP32_CONFIG_H

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include "ConfigParam.h"

const char HTTP_HEADER[]                    = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/><title>{v}</title>";
const char HTTP_STYLE[]                     = "<style>.c{text-align: center;} div,input{padding:5px;font-size:1em;} input{width:95%;margin-top:3px;margin-bottom:3px;} body{text-align: center;font-family:verdana;} button{border:0;border-radius:0.3rem;background-color:#1fa3ec;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;margin-top:3px;} .q{float: right;width: 64px;text-align: right;} .l{background: url(\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAMAAABEpIrGAAAALVBMVEX///8EBwfBwsLw8PAzNjaCg4NTVVUjJiZDRUUUFxdiZGSho6OSk5Pg4eFydHTCjaf3AAAAZElEQVQ4je2NSw7AIAhEBamKn97/uMXEGBvozkWb9C2Zx4xzWykBhFAeYp9gkLyZE0zIMno9n4g19hmdY39scwqVkOXaxph0ZCXQcqxSpgQpONa59wkRDOL93eAXvimwlbPbwwVAegLS1HGfZAAAAABJRU5ErkJggg==\") no-repeat left center;background-size: 1em;}</style>";
const char HTTP_SCRIPT[]                    = "<script>function c(l){document.getElementById('s').value=l.innerText||l.textContent;document.getElementById('p').focus();}</script>";
const char HTTP_HEADER_END[]                = "</head><body><div style='text-align:left;display:inline-block;min-width:260px;'>";
const char HTTP_ITEM[]                      = "<div><a href='#p' onclick='c(this)'>{v}</a>&nbsp;<span class='q {i}'>{r}%</span></div>";
const char HTTP_FORM_START[]                = "<form method='get' action='wifisave'><input id='s' name='s' length=32 placeholder='SSID' required><br/><input id='p' name='p' length=64 type='password' placeholder='password' required><hr/>";
const char HTTP_FORM_INPUT[]                = "<input id='{i}' name='{n}' placeholder='{p}' maxlength={l} value='{v}' {c}><br/>";
const char HTTP_FORM_INPUT_LIST[]           = "<input id='{i}' name='{n}' placeholder='{p}' list='d' {c}><datalist id='d'{o}></datalist><br/>";
const char HTTP_FORM_INPUT_LIST_OPTION[]    = "<option>{o}</option>";
const char HTTP_FORM_END[]                  = "<hr/><button type='submit'>Save</button></form>";
const char HTTP_SCAN_LINK[]                 = "<br/><div class=\"c\"><a href=\"/scan\">Scan for networks</a></div>";
const char HTTP_SAVED[]                     = "<div>Credentials Saved<br/>Trying to connect ESP to network.<br/>If it fails reconnect to AP to try again</div>";
const char HTTP_END[]                       = "</div></body></html>";

#ifndef INVALID_PIN_NO
#define INVALID_PIN_NO 255
#endif

class ESP32Config {
    public:
        ESP32Config();
        ~ESP32Config();

        /* launch methods */
        bool            connectWifiNetwork(bool existConfig);
        bool            startConfigPortal();

        /* setup methods */
        /* Set wifi connect timeout in millis */
        void            setWifiConnectTimeout(unsigned long seconds);
        void            setConfigPortalTimeout(unsigned long seconds);
        void            setPortalSSID(const char *apName);
        void            setPortalPassword(const char *apPass);
        bool            addParameter(ConfigParam *p);
        void            setFeedbackPin(uint8_t pin);
        void            setAPStaticIP(IPAddress ip, IPAddress gw, IPAddress sn);
        
        // Returns the param under the specified index
        ConfigParam *getParameter(uint8_t index);

        // Returns the numer of params existing
        uint8_t     getParamsCount();

        //called when AP mode and config portal is started
        void        setAPCallback (std::function<void(ESP32Config*)> callback);
        
        //called when connecting station to AP
        void        setStationNameCallback (std::function<const char*(void)> callback);
        
        //called when settings have been changed and connection was successful
        void        setSaveConfigCallback (std::function<void(void)> callback);
        
        //defaults to not showing anything under 8% signal quality if called
        void        setMinimumSignalQuality (int quality = 8);

        // Blocking signal feedback. Turns on/off a signal a specific times waiting a step time for each state flip.
        void        blockingFeedback (uint8_t pin, long stepTime, uint8_t times);

        // Non blocking signal feedback (to be used inside a loop). Uses global variables to control when to flip the signal state according to the step time.
        void        nonBlockingFeedback (uint8_t pin, int stepTime);

    private:

        std::unique_ptr<DNSServer>  _dnsServer;
        std::unique_ptr<WebServer>  _server;
        
        const char*     _apName             = "ESP-Module";
        const char*     _apPass             = NULL;
        int             _minimumQuality     = -1;
        uint8_t         _paramsCount        = 0;
        uint8_t         _max_params;
        bool            _connect;
        uint8_t         _feedbackPin        = INVALID_PIN_NO;

        const uint8_t   DNS_PORT            = 53;

        uint8_t connectWifi(String ssid, String pass);
        uint8_t connectWiFi();
        uint8_t waitForConnectResult();
        void    setupConfigPortal();

        unsigned long       _wifiConnectTimeout;
        unsigned long       _configPortalTimeout;
        unsigned long       _configPortalStart;
        
        // Signal feedback
        bool                _sigfbkIsOn           = false;
        unsigned long       _sigfbkStepControl    = 0;
        ConfigParam**    _configParams;
        
        IPAddress           _ap_static_ip;
        IPAddress           _ap_static_gw;
        IPAddress           _ap_static_sn;

        /* Callbacks */
        std::function<void(ESP32Config*)>   _apcallback;
        std::function<const char*(void)>    _stationNameCallback;
        std::function<void(void)>           _savecallback;
        
        void        handleWifi(bool scan);
        void        handleWifiSave();
        void        handleNotFound();
        bool        captivePortal();
        bool        configPortalHasTimeout();
        bool        isIp(String str);
        String      toStringIp(IPAddress ip);
        int         getRSSIasQuality(int RSSI);

        #ifdef LOGGING
        template <class T> void debug(T text);
        template <class T, class U> void debug(T key, U value);
        #endif
};

#endif