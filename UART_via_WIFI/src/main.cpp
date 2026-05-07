#include <Arduino.h>
#include "config.h"
#include "NetworkManager.h"
#include "UartBridge.h"

NetworkManager net;
UartBridge bridge;

void setup() {
    // Hạ xung nhịp CPU xuống 80MHz để giảm nhiệt độ (mặc định 160MHz)
    setCpuFrequencyMhz(80);

    Serial.begin(DEBUG_BAUD);
    Serial1.begin(RM200_BAUD, SERIAL_8N1, RM200_RX_PIN, RM200_TX_PIN);

    // Gửi ngay ra Serial1 để test link với con S3
    for(int i=0; i<5; i++) {
        Serial1.println(">>> C3 TO S3 LINK TEST OK <<<");
        delay(100);
    }

    unsigned long waitStart = millis();
    while (!Serial && (millis() - waitStart < 3000)) {
        delay(10);
    }
    delay(1000);
    
    // In ra cả 2 cổng để debug tiện lợi
    const char* header = "\n--- UART to TCP Server Bridge ---";
    Serial.println(header);
    Serial1.println(header);

    Serial.printf("Debug baud: %d\n", DEBUG_BAUD);
    Serial1.printf("Debug baud: %d\n", DEBUG_BAUD);

    Serial.printf("UART1 config: baud=%d RX=%d TX=%d\n", RM200_BAUD, RM200_RX_PIN, RM200_TX_PIN);
    Serial1.printf("UART1 config: baud=%d RX=%d TX=%d\n", RM200_BAUD, RM200_RX_PIN, RM200_TX_PIN);

    net.begin(WIFI_SSID, WIFI_PASS);
    // Kích hoạt Modem Sleep để giảm nhiệt cho khối Radio WiFi
    WiFi.setSleep(true);
}

void loop() {
    // --- 1. ĐỌC LỆNH TỪ CUTECOM (USB) -> GỬI XUỐNG MODULE & WEB ---
    while (Serial.available()) {
        char c = Serial.read();
        Serial1.write(c);            
        Serial.write(c);             
        bridge.injectToServer(c);    
        bridge.notifyUartActivity(); // Có lệnh từ USB cũng tính là hoạt động UART
    }

    // --- 2. ĐỌC PHẢN HỒI TỪ MODULE (SERIAL1) -> GỬI LÊN WEB & USB ---
    while (Serial1.available()) {
        char c = Serial1.read();
        Serial.write(c);             // Hiển thị lên màn hình Debug (USB)
        bridge.injectToServer(c);    // Gửi lên Web Server
    }
    // ---------------------------------

    net.checkStatus();
    
    // Theo dõi trạng thái WiFi
    static bool lastWifi = false;
    bool currentWifi = net.isConnected();
    if (currentWifi && !lastWifi) { 
        Serial.print("\n--- WiFi Connected! ---\n");
        Serial1.print("\n--- WiFi Connected! ---\n");
        
        Serial.printf("Connecting to Server: %s:%d\n", SERVER_DOMAIN, SERVER_PORT);
        Serial1.printf("Connecting to Server: %s:%d\n", SERVER_DOMAIN, SERVER_PORT);
        
        bridge.connect(SERVER_DOMAIN, SERVER_PORT);
    }
    lastWifi = currentWifi;

    bridge.update();

    // --- TÍNH NĂNG THEO DÕI TRẠNG THÁI (Chỉ in 1 lần khi thay đổi) ---
    static bool lastBridge = false;
    bool currentBridge = bridge.isClientConnected();
    
    if (currentBridge != lastBridge) {
        if (currentBridge) {
            const char* msg = "\n[STATUS] TCP Bridge is CONNECTED! Ready to transfer data.";
            Serial.println(msg);
            Serial1.println(msg);
        } else {
            const char* msg = "\n[STATUS] TCP Bridge DISCONNECTED! Waiting to reconnect...";
            Serial.println(msg);
            Serial1.println(msg);
        }
        lastBridge = currentBridge;
    }
    // -----------------------------------------------------------------

    NetStatus currentStatus;
    if (!net.isConnected()) {
        currentStatus = STATUS_WIFI_DISCONNECTED;
    } else if (!bridge.isClientConnected()) {
        currentStatus = STATUS_WIFI_CONNECTED;
    } else {
        currentStatus = STATUS_BRIDGE_CONNECTED;
    }
    net.updateLED(currentStatus);

    // Cho CPU nghỉ 1ms mỗi vòng lặp để RTOS xử lý tác vụ nền và hạ nhiệt
    delay(1);
}
