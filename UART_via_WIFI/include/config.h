#ifndef CONFIG_H
#define CONFIG_H

// --- Cấu hình Wi-Fi ---
#define WIFI_SSID "UIT PubliC"
#define WIFI_PASS "mehehehe" // Mật khẩu được bảo mật (hãy điền pass thật khi test)

// --- Cấu hình TCP Server (Web của giảng viên) ---
#define SERVER_IP "172.16.214.213" // IP của Server (Thay đổi theo IP thực tế của thầy)
#define SERVER_PORT 8080          // Port lắng nghe của Server

// --- Cấu hình hệ thống ---
#define DEBUG_BAUD 115200
#define RM200_BAUD 115200
#define RM200_RX_PIN 10
#define RM200_TX_PIN 9
#define STATUS_LED_PIN 8

// --- Tham số Gom gói (Aggregation) ---
#define UART_AGGREGATION_MS 5
#define BUFFER_SIZE 1024

#endif