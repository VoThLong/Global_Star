#ifndef UART_BRIDGE_H
#define UART_BRIDGE_H

#include <WiFi.h>
#include "config.h"

class UartBridge {
public:
    // Chế độ Server: Chờ Client kết nối tới Port
    void begin(uint16_t port);
    
    // Chế độ Client: Chủ động kết nối tới IP/Port của Server khác (ví dụ Portal)
    void connect(IPAddress remoteIP, uint16_t remotePort);
    
    void update();
    bool isClientConnected();
    void injectToServer(uint8_t data);

private:
    void ensureUartReady();

    WiFiServer* _server = nullptr;
    WiFiClient _client;
    
    // Thông tin cho chế độ Client chủ động
    IPAddress _remoteIP;
    uint16_t _remotePort = 0;
    bool _isActiveClientMode = false;
    unsigned long _lastReconnectAttempt = 0;

    // Buffer gom gói dữ liệu UART
    uint8_t _uartBuffer[BUFFER_SIZE];
    size_t _bufferCount = 0;
    unsigned long _lastByteTime = 0;
    bool _uartReady = false;
    size_t _uartRxSinceReport = 0;
    unsigned long _lastUartReport = 0;
};

#endif
