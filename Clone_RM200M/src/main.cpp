#include <Arduino.h>
#include "config.h"

static unsigned long lastHeartbeatMs = 0;
static unsigned long totalRxBytes = 0;

void setup() {
  // USB serial monitor
  Serial.begin(UART_BAUD);

  // Cho host USB có thời gian kết nối, tránh log đầu bị mất.
  unsigned long waitStart = millis();
  while (!Serial && (millis() - waitStart) < 1500) {
    delay(10);
  }

  Serial.println("\n\n===============================");
  Serial.println("ESP32-S3 UART Debug Bridge Starting...");
  Serial.print("UART1 RX Pin: "); Serial.println(PIN_RX_IN);
  Serial.print("UART1 TX Pin: "); Serial.println(PIN_TX_OUT);
  Serial.print("UART Baud   : "); Serial.println(UART_BAUD);

  // UART1 qua pin matrix, dùng chân do config.h khai báo.
  Serial1.setRxBufferSize(1024);
  Serial1.begin(UART_BAUD, SERIAL_8N1, PIN_RX_IN, PIN_TX_OUT);

  Serial.println("Bridge Ready - Transparent Mode");
  Serial.println("Type on USB monitor => sent to UART1 TX");
  Serial.println("Bytes from UART1 RX => printed to USB monitor");
  Serial.println("===============================");
}

void loop() {
  int moved = 0;
  while (Serial.available() && moved < 256) {
    int c = Serial.read();
    if (c >= 0) {
      Serial1.write(static_cast<uint8_t>(c));
      moved++;
    }
  }

  while (Serial1.available() && moved < 512) {
    int c = Serial1.read();
    if (c >= 0) {
      Serial.write(static_cast<uint8_t>(c));
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
