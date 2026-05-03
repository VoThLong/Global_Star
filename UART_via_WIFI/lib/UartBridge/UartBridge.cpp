#include "UartBridge.h"

UartBridge::UartBridge() : bufferIdx(0), lastByteTime(0), serverAvailable(false) {
    memset(buffer, 0, BUFFER_SIZE);
}

void UartBridge::connect(IPAddress ip, uint16_t port) {
    // Với HTTP, ta không giữ kết nối liên tục như TCP
    serverAvailable = true;
    Serial.println("[HTTP] UartBridge ready in HTTP mode");
}

void UartBridge::injectToServer(char c) {
    if (bufferIdx < BUFFER_SIZE - 1) {
        buffer[bufferIdx++] = c;
        lastByteTime = millis();
    }
}

void UartBridge::update() {
    // 1. Gửi dữ liệu UART lên Web (Gom gói)
    if (bufferIdx > 0 && (millis() - lastByteTime > UART_AGGREGATION_MS)) {
        buffer[bufferIdx] = '\0';
        sendDataToWeb(String(buffer));
        bufferIdx = 0;
        memset(buffer, 0, BUFFER_SIZE);
    }

    // 2. Định kỳ lấy lệnh từ Web về (Poll)
    static unsigned long lastPoll = 0;
    if (millis() - lastPoll > 1000) { // Poll mỗi 1 giây
        pollCommandFromWeb();
        lastPoll = millis();
    }
}

void UartBridge::sendDataToWeb(String data) {
    if (WiFi.status() != WL_CONNECTED) return;

    HTTPClient http;
    http.begin(API_UPLOAD);
    http.addHeader("Content-Type", "text/plain"); // Gửi dạng văn bản thuần túy

    int httpResponseCode = http.POST(data); // Gửi trực tiếp chuỗi data thô
    
    if (httpResponseCode > 0) {
        // Thành công
    } else {
        Serial.printf("[HTTP] Send failed, error: %s\n", http.errorToString(httpResponseCode).c_str());
    }
    http.end();
}

void UartBridge::pollCommandFromWeb() {
    if (WiFi.status() != WL_CONNECTED) return;

    HTTPClient http;
    http.begin(API_COMMAND);
    
    int httpResponseCode = http.GET();
    
    if (httpResponseCode == 200) {
        String payload = http.getString();
        if (payload.length() > 0) {
            Serial.print("\n[WEB CMD] Received: ");
            Serial.println(payload);
            
            // Gửi lệnh xuống Module RM200M qua Serial1 kèm theo ký tự xuống dòng
            Serial1.println(payload); 
            
            // Phản hồi ngược lại Web Server để xác nhận đã nhận lệnh (nếu cần)
            // Ở đây ta có thể in ra Serial để người dùng thấy trên CuteCom
            Serial.print(">> Sent to RM200M: ");
            Serial.println(payload);
        }
    }
    http.end();
}

bool UartBridge::isClientConnected() {
    return WiFi.status() == WL_CONNECTED;
}
