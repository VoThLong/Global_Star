#ifndef UART_BRIDGE_H
#define UART_BRIDGE_H

#include <Arduino.h>
#include <HTTPClient.h>
#include "config.h"

class UartBridge {
public:
    UartBridge();
    void connect(IPAddress ip, uint16_t port); // Giữ lại để tương thích main.cpp
    void update();
    void injectToServer(char c);
    bool isClientConnected();

private:
    char buffer[BUFFER_SIZE];
    int bufferIdx;
    unsigned long lastByteTime;
    bool serverAvailable;
    
    void sendDataToWeb(String data);
    void pollCommandFromWeb();
    void sendHeartbeat();
    unsigned long lastHeartbeat;
};

#endif
