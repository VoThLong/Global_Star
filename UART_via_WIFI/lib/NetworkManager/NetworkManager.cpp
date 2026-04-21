#include "NetworkManager.h"
#include <Arduino.h>

void NetworkManager::begin(const char* ssid, const char* pass) {
    pinMode(STATUS_LED_PIN, OUTPUT);
    digitalWrite(STATUS_LED_PIN, LOW);
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    Serial.printf("\nConnecting to WiFi: %s\n", ssid);
}

void NetworkManager::checkStatus() {
    static unsigned long lastCheck = 0;
    if (millis() - lastCheck > 5000) { // Check every 5s
        lastCheck = millis();
        if (WiFi.status() != WL_CONNECTED) {
            Serial.println("WiFi not connected. Retrying...");
            // WiFi.begin() already handles auto-reconnect, 
            // but we can call reconnect() if it stays disconnected too long.
            if (WiFi.status() == WL_IDLE_STATUS || WiFi.status() == WL_CONNECT_FAILED) {
                WiFi.reconnect();
            }
        }
    }
}

void NetworkManager::updateLED(NetStatus status) {
    unsigned long now = millis();
    unsigned long interval = 0;

    switch (status) {
        case STATUS_WIFI_DISCONNECTED:
            interval = 1000; // Slow blink
            break;
        case STATUS_WIFI_CONNECTED:
            interval = 200;  // Fast blink
            break;
        case STATUS_BRIDGE_CONNECTED:
            digitalWrite(STATUS_LED_PIN, HIGH); // Solid ON
            return;
    }

    if (now - _lastBlink >= interval) {
        _lastBlink = now;
        _ledState = !_ledState;
        digitalWrite(STATUS_LED_PIN, _ledState);
    }
}

bool NetworkManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

IPAddress NetworkManager::getIP() {
    return WiFi.localIP();
}
