#include <Arduino.h>
#include "config.h"

static unsigned long lastHeartbeatMs = 0;
static unsigned long totalRxBytes = 0;

void setup() {
  // USB serial monitor (UART0 via CH340)
  Serial.begin(115200);
  delay(2000);

  Serial.println("\n\n[SYSTEM] ESP32-S3 Bridge Starting...");
  Serial.printf("[SYSTEM] Baudrate: %d, RX:%d, TX:%d\n", UART_BAUD, PIN_RX_IN, PIN_TX_OUT);

  // Xóa trắng buffer Serial1 trước khi bắt đầu
  Serial1.begin(UART_BAUD, SERIAL_8N1, PIN_RX_IN, PIN_TX_OUT); 
  while(Serial1.available()) Serial1.read();
  
  // Simple TX test
  delay(500);
  for(int i = 0; i < 5; i++) {
    Serial.println("[S3] UART1 TX TEST");
    Serial1.println("[S3] If C3 sees this, UART1 TX works!");
    delay(100);
  }
  
  Serial.println("[SYSTEM] Ready.");
  Serial.println("===============================");
}

void loop() {
  int moved = 0;
  while (Serial.available() && moved < 256) {
    int c = Serial.read();
    if (c >= 0) {
      Serial1.write(static_cast<uint8_t>(c));
      Serial.write(static_cast<uint8_t>(c)); // Echo back to USB for debugging
      moved++;
    }
  }

  while (Serial1.available() && moved < 512) {
    int c = Serial1.read();
    if (c >= 0) {
      Serial.write(static_cast<uint8_t>(c)); // In tất cả bytes (printable hoặc control)
      totalRxBytes++;
      moved++;
    }
  }

  if (moved == 0) {
    unsigned long now = millis();
    if (now - lastHeartbeatMs >= 2000) {
      lastHeartbeatMs = now;
      Serial.print("[S3 alive] rx_bytes=");
      Serial.println(totalRxBytes);
    }
    delay(1);
  } else {
    yield();
  }
}
