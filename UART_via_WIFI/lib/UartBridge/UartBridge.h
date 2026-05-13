#ifndef UART_BRIDGE_H
#define UART_BRIDGE_H

#include <Arduino.h>
#include <HTTPClient.h>
#include "config.h"

#define MAX_OFFLINE_BUFFER 20 // Lưu tối đa 20 bản tin khi mất mạng

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
    unsigned long lastUartActivityTime; 
    
    // --- Cơ chế bộ đệm ngoại tuyến (Offline Buffering) ---
    String offlineBuffer[MAX_OFFLINE_BUFFER];
    int offlineCount;
    bool sendDataToWeb(String data); // Trả về true nếu gửi thành công
    // -----------------------------------------------------

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
