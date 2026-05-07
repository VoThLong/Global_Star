#ifndef CONFIG_H
#define CONFIG_H

// --- Cấu hình Wi-Fi ---
#define WIFI_SSID "TTLAB2024"
#define WIFI_PASS "123322456" 

// --- Cấu hình Web Server ---
#define SERVER_DOMAIN "manhthao.uk"
#define SERVER_PORT 53000

// Các Endpoint HTTP
#define API_UPLOAD "http://manhthao.uk:53000/upload"
#define API_COMMAND "http://manhthao.uk:53000/command"

// --- Cấu hình hệ thống ---
#define DEBUG_BAUD 115200
#define RM200_BAUD 115200

#define RM200_RX_PIN 4
#define RM200_TX_PIN 6

#define STATUS_LED_PIN 8
// --- Tham số Gom gói (Aggregation) ---
#define UART_AGGREGATION_MS 50 // Tăng lên một chút để gom gói HTTP hiệu quả hơn
#define BUFFER_SIZE 2048

#endif
