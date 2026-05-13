#include "UartBridge.h"

UartBridge::UartBridge() : bufferIdx(0), lastByteTime(0), serverAvailable(false), queueHead(0), queueTail(0), currentCmdId(""), lastUartActivityTime(0), offlineCount(0) {
    memset(buffer, 0, BUFFER_SIZE);
}

void UartBridge::connect(const char* host, uint16_t port) {
    serverAvailable = true;
    Serial.printf("[HTTP] UartBridge ready for host: %s\n", host);
}

void UartBridge::injectToServer(char c) {
    lastUartActivityTime = millis(); 
    if (bufferIdx < BUFFER_SIZE - 1) {
        if (bufferIdx == 0 && currentCmdId.length() > 0) {
            String prefix = "[" + currentCmdId + "] ";
            for (int i = 0; i < (int)prefix.length(); i++) {
                if (bufferIdx < BUFFER_SIZE - 1) buffer[bufferIdx++] = prefix[i];
            }
        }
        buffer[bufferIdx++] = c;
        lastByteTime = millis();
    }
}

void UartBridge::notifyUartActivity() {
    lastUartActivityTime = millis();
}

void UartBridge::update() {
    // 1. Xử lý dữ liệu UART mới (Gom gói)
    if (bufferIdx > 0 && (millis() - lastByteTime > UART_AGGREGATION_MS)) {
        buffer[bufferIdx] = '\0';
        String data = String(buffer);
        
        if (currentCmdId == "" && data.indexOf("+URC:") != -1) {
            data = "[#URC_SYS] " + data;
        }

        // Thử gửi ngay
        if (!sendDataToWeb(data)) {
            // Nếu gửi thất bại, lưu vào bộ đệm offline
            if (offlineCount < MAX_OFFLINE_BUFFER) {
                offlineBuffer[offlineCount++] = data;
                Serial.printf("[BUFFER] Saved to offline queue (%d/%d)\n", offlineCount, MAX_OFFLINE_BUFFER);
            } else {
                Serial.println("[BUFFER] Queue full, data lost!");
            }
        }

        bufferIdx = 0;
        memset(buffer, 0, BUFFER_SIZE);
        currentCmdId = ""; 
    }

    // 2. Xả bộ đệm offline khi có mạng lại (Mỗi lần update chỉ gửi 1 gói để tránh nghẽn)
    if (WiFi.status() == WL_CONNECTED && offlineCount > 0) {
        static unsigned long lastFlush = 0;
        if (millis() - lastFlush > 500) { // Giãn cách 500ms mỗi gói xả
            if (sendDataToWeb("[OFFLINE] " + offlineBuffer[0])) {
                // Gửi thành công, dịch chuyển mảng sang trái
                for (int i = 0; i < offlineCount - 1; i++) {
                    offlineBuffer[i] = offlineBuffer[i+1];
                }
                offlineCount--;
                Serial.printf("[BUFFER] Flushed 1 item, remaining: %d\n", offlineCount);
            }
            lastFlush = millis();
        }
    }

    // 3. Xử lý timeout lệnh
    if (currentCmdId != "" && (millis() - lastCmdSentTime > 3000)) {
        String errMsg = "[" + currentCmdId + "] Error: Response Timeout (3s)";
        if (!sendDataToWeb(errMsg) && offlineCount < MAX_OFFLINE_BUFFER) {
            offlineBuffer[offlineCount++] = errMsg;
        }
        currentCmdId = ""; 
    }

    if (currentCmdId == "" && queueHead != queueTail) {
        currentCmdId = cmdQueue[queueHead].id;
        String actualCmd = cmdQueue[queueHead].cmd;
        sendDataToWeb("__ACK__:" + currentCmdId);

        // --- TARGETED WAKE-UP ---
        // Chỉ đánh thức khi rảnh quá 5 giây
        if (millis() - lastUartActivityTime > 5000) {
            Serial.println("[UART] Idle > 5s, sending wake-up byte before command...");
            Serial1.write('\r');
            delay(50);
        }
        // ------------------------

        Serial1.println(actualCmd);
        Serial1.flush();
        lastCmdSentTime = millis();
        lastUartActivityTime = millis();
        queueHead = (queueHead + 1) % 20;
    }

    static unsigned long lastPoll = 0;
    if (millis() - lastPoll > 1000) {
        pollCommandFromWeb();
        lastPoll = millis();
    }
}

bool UartBridge::sendDataToWeb(String data) {
    if (WiFi.status() != WL_CONNECTED) return false;
    HTTPClient http;
    http.setConnectTimeout(2000); // Timeout 2s để tránh treo nếu mạng lag
    http.begin(API_UPLOAD);
    http.addHeader("Content-Type", "text/plain");
    int httpResponseCode = http.POST(data);
    http.end();
    return (httpResponseCode == 200);
}

void UartBridge::pollCommandFromWeb() {
    if (WiFi.status() != WL_CONNECTED) return;
    HTTPClient http;
    http.setConnectTimeout(1000); 
    http.begin(API_COMMAND);
    int httpResponseCode = http.GET();
    if (httpResponseCode == 200) {
        String payload = http.getString();
        if (payload.length() > 0) {
            int startIdx = 0;
            int endIdx = payload.indexOf('\n');
            while (true) {
                String line = (endIdx == -1) ? payload.substring(startIdx) : payload.substring(startIdx, endIdx);
                line.trim();
                if (line.length() > 0) {
                    int sepIdx = line.indexOf('|');
                    if (sepIdx != -1) {
                        String id = line.substring(0, sepIdx);
                        String cmd = line.substring(sepIdx + 1);
                        int nextTail = (queueTail + 1) % 20;
                        if (nextTail != queueHead) {
                            cmdQueue[queueTail].id = id;
                            cmdQueue[queueTail].cmd = cmd;
                            queueTail = nextTail;
                        }
                    }
                }
                if (endIdx == -1) break;
                startIdx = endIdx + 1;
                endIdx = payload.indexOf('\n', startIdx);
            }
        }
    }
    http.end();
}

bool UartBridge::isClientConnected() {
    return WiFi.status() == WL_CONNECTED;
}
