#ifndef UART_BRIDGE_H
#define UART_BRIDGE_H

#include <Arduino.h>
#include <HTTPClient.h>
#include "config.h"

class UartBridge {
public:
    UartBridge();
    void connect(const char* host, uint16_t port); 
    void update();
    void injectToServer(char c);
    void notifyUartActivity();
    bool isClientConnected();

private:
    char buffer[BUFFER_SIZE];
    int bufferIdx;
    unsigned long lastByteTime;
    bool serverAvailable;
    unsigned long lastUartActivityTime; // Theo dõi lần cuối có dữ liệu qua lại UART
    
    void sendDataToWeb(String data);
    void pollCommandFromWeb();
    
    struct PendingCmd {
        String id;
        String cmd;
    };
    PendingCmd cmdQueue[20];
    int queueHead = 0;
    int queueTail = 0;
    String currentCmdId;
    unsigned long lastCmdSentTime;
};

#endif
