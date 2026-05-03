#include <Arduino.h>
#include "config.h"
#include "NetworkManager.h"
#include "UartBridge.h"

NetworkManager net;
UartBridge bridge;

void setup() {
    Serial.begin(DEBUG_BAUD);
    unsigned long waitStart = millis();
    while (!Serial && (millis() - waitStart < 3000)) {
        delay(10);
    }
    delay(1000);
    Serial.println("\n--- UART to TCP Server Bridge ---");
    Serial.printf("Debug baud: %d\n", DEBUG_BAUD);
    Serial.printf("UART1 config: baud=%d RX=%d TX=%d\n", RM200_BAUD, RM200_RX_PIN, RM200_TX_PIN);
    Serial1.begin(RM200_BAUD, SERIAL_8N1, RM200_RX_PIN, RM200_TX_PIN);
    net.begin(WIFI_SSID, WIFI_PASS);
}

void loop() {
    // --- 1. ĐỌC LỆNH TỪ CUTECOM (USB) -> GỬI XUỐNG MODULE & WEB ---
    while (Serial.available()) {
        char c = Serial.read();
        Serial1.write(c);            
        Serial.write(c);             
        bridge.injectToServer(c);    
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
        Serial.printf("Connecting to Server: %s:%d\n", SERVER_IP, SERVER_PORT);
        
        IPAddress targetIP;
        targetIP.fromString(SERVER_IP);
        bridge.connect(targetIP, SERVER_PORT);
    }
    lastWifi = currentWifi;

    bridge.update();

    // --- TÍNH NĂNG THEO DÕI TRẠNG THÁI (Chỉ in 1 lần khi thay đổi) ---
    static bool lastBridge = false;
    bool currentBridge = bridge.isClientConnected();
    
    if (currentBridge != lastBridge) {
        if (currentBridge) {
            Serial.println("\n[STATUS] TCP Bridge is CONNECTED! Ready to transfer data.");
        } else {
            Serial.println("\n[STATUS] TCP Bridge DISCONNECTED! Waiting to reconnect...");
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
}