#ifndef CONFIG_H
#define CONFIG_H

// --- Cấu hình Wi-Fi ---
#define WIFI_SSID "UIT PubliC"
#define WIFI_PASS "mehehehe" 

// --- Cấu hình Web Server ---
#define SERVER_IP "192.168.1.17"
#define SERVER_PORT 3000

// Các Endpoint HTTP
#define API_UPLOAD "http://192.168.1.17:3000/upload"
#define API_COMMAND "http://192.168.1.17:3000/command"

// --- Cấu hình hệ thống ---
#define DEBUG_BAUD 115200
#define RM200_BAUD 115200
#define RM200_RX_PIN 10
#define RM200_TX_PIN 9
#define STATUS_LED_PIN 8

// --- Tham số Gom gói (Aggregation) ---
#define UART_AGGREGATION_MS 50 // Tăng lên một chút để gom gói HTTP hiệu quả hơn
#define BUFFER_SIZE 2048

#endif
