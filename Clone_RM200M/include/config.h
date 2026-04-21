#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ESP32-S3 UART1 mặc định: RX=18, TX=17.
// Đổi theo wiring thực tế nếu bạn đang đấu cặp chân khác.
#define PIN_RX_IN 18
#define PIN_TX_OUT 17

#define UART_BAUD 115200

#endif
