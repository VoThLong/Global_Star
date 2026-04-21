#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <WiFi.h>
#include "config.h"

enum NetStatus {
    STATUS_WIFI_DISCONNECTED,
    STATUS_WIFI_CONNECTED,
    STATUS_BRIDGE_CONNECTED
};

class NetworkManager {
public:
    void begin(const char* ssid, const char* pass);
    void checkStatus(); // Reconnect if needed
    void updateLED(NetStatus status);
    bool isConnected();
    IPAddress getIP();
private:
    unsigned long _lastBlink = 0;
    bool _ledState = false;
};

#endif
