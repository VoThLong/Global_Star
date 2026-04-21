#include "UartBridge.h"
#include <Arduino.h>

void UartBridge::ensureUartReady() {
    if (_uartReady) return;
    Serial1.begin(RM200_BAUD, SERIAL_8N1, RM200_RX_PIN, RM200_TX_PIN);
    _uartReady = true;
    Serial.printf("Bridge: UART initialized at %d baud (RX=%d, TX=%d)\n",
                  RM200_BAUD, RM200_RX_PIN, RM200_TX_PIN);
}

void UartBridge::begin(uint16_t port) {
    _isActiveClientMode = false;
    ensureUartReady();
    
    _server = new WiFiServer(port);
    _server->begin();
    Serial.printf("Bridge: Server mode started on port %d\n", port);
}

void UartBridge::connect(IPAddress remoteIP, uint16_t remotePort) {
    _isActiveClientMode = true;
    _remoteIP = remoteIP;
    _remotePort = remotePort;
    
    ensureUartReady();
    Serial.printf("Bridge: Client mode configured to connect to Portal at %s:%d\n", 
                  _remoteIP.toString().c_str(), _remotePort);
}

void UartBridge::update() {
    ensureUartReady();
    unsigned long now = millis();

    // 1. Quản lý kết nối
    if (_isActiveClientMode) {
        // CHẾ ĐỘ CLIENT: Chủ động kết nối/kết nối lại
        if (!_client.connected()) {
            unsigned long now = millis();
            if (now - _lastReconnectAttempt > 5000) { // Thử lại mỗi 5s
                _lastReconnectAttempt = now;
                Serial.printf("Connecting to Portal %s:%d...\n", _remoteIP.toString().c_str(), _remotePort);
                if (_client.connect(_remoteIP, _remotePort)) {
                    _client.setNoDelay(true);
                    Serial.println("Connected to Portal!");
                }
            }
        }
    } else if (_server != nullptr) {
        // CHẾ ĐỘ SERVER: Chờ Client mới
        if (_server->hasClient()) {
            WiFiClient newClient = _server->available();
            if (newClient) {
                if (_client && _client.connected()) {
                    _client.stop();
                    Serial.println("Closed old client for new connection.");
                }
                _client = newClient;
                _client.setNoDelay(true);
                Serial.printf("\n--- New client connected from %s ---\n", _client.remoteIP().toString().c_str());
                _bufferCount = 0;
            }
        }
    }

    // 2. Xử lý dữ liệu (Chỉ khi đã có kết nối)
    if (_client && _client.connected()) {
        // WiFi -> UART
        while (_client.available()) {
            uint8_t webByte = static_cast<uint8_t>(_client.read());
            Serial1.write(webByte);
            Serial.write(webByte); // In lệnh từ Server web ra màn hình Serial
        }

        // UART -> WiFi (Gom gói 5ms)
        while (Serial1.available() && _bufferCount < BUFFER_SIZE) {
            uint8_t byteRead = static_cast<uint8_t>(Serial1.read());
            _uartBuffer[_bufferCount++] = byteRead;
            Serial.write(byteRead); // In phản hồi từ Vệ tinh ra màn hình Serial
            _uartRxSinceReport++;
            _lastByteTime = millis();
        }

        if (_bufferCount > 0 && (millis() - _lastByteTime >= UART_AGGREGATION_MS)) {
            _client.write(_uartBuffer, _bufferCount);
            _bufferCount = 0;
        }
    } else {
        // Mirror dữ liệu UART lên Serial Monitor ngay cả khi chưa có client TCP.
        while (Serial1.available()) {
            uint8_t byteRead = static_cast<uint8_t>(Serial1.read());
            Serial.write(byteRead);
            _uartRxSinceReport++;
        }
        _bufferCount = 0;
    }

    if (now - _lastUartReport >= 1000) {
        if (_uartRxSinceReport > 0) {
            Serial.printf("\n[UART] RX %u bytes/s\n", static_cast<unsigned>(_uartRxSinceReport));
            _uartRxSinceReport = 0;
        }
        _lastUartReport = now;
    }
}

bool UartBridge::isClientConnected() {
    return (_client && _client.connected());
}

void UartBridge::injectToServer(uint8_t data) {
    // Nhét trực tiếp ký tự từ USB vào bộ đệm TCP (Gom gói 5ms)
    if (_bufferCount < BUFFER_SIZE) {
        _uartBuffer[_bufferCount++] = data;
        _lastByteTime = millis();
    }
}
