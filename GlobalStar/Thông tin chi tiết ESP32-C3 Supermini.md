# Hướng Dẫn Kỹ Thuật: ESP32-C3 Supermini (Bản 16 chân)

Tài liệu này tổng hợp các thông số kỹ thuật cốt lõi, sơ đồ chân và cách thức thiết lập để lập trình cho board mạch ESP32-C3 Supermini.

## 1. Thông Số Kỹ Thuật Phân Cứng

### Vi xử lý và Bộ nhớ

- **MCU:** ESP32-C3 lõi đơn 32-bit RISC-V.
    
- **Xung nhịp:** Tối đa 160 MHz.
    
- **Tích hợp phần cứng:** Bộ tính toán dấu phẩy động (FPU) tối ưu cho xử lý toán học.
    
- **SRAM / ROM:** 400 KB / 384 KB.
    
- **Flash:** 4 MB SPI Flash (tích hợp trên board).
    

### Kết nối không dây

- **Wi-Fi:** Chuẩn 802.11 b/g/n (2.4 GHz).
    
- **Bluetooth:** Bluetooth 5.0 (BLE - Bluetooth Low Energy), có hỗ trợ Bluetooth Mesh.
    

### Giao tiếp và I/O

- **Kích thước:** Siêu nhỏ gọn (~22.5 x 18 mm).
    
- **GPIO:** Tổng cộng 11 chân IO độc lập.
    
- **Chức năng chân:** Tất cả 11 chân đều hỗ trợ PWM và Interrupt (ngắt).
    
- **ADC:** 6 kênh ADC 12-bit (chạy trên các chân từ IO0 đến IO5).
    
- **Giao tiếp:** 1x I2C, 1x SPI, 2x UART.
    
- **USB:** Cổng Type-C. Lõi ESP32-C3 hỗ trợ USB CDC (nạp code trực tiếp không cần IC chuyển đổi CH340/CP2102).
    

### Nguồn điện

- **Điện áp logic GPIO:** **3.3V** (Tuyệt đối không cấp tín hiệu 5V vào các chân IO).
    
- **Nguồn cấp:** Cấp 5V qua cổng USB-C hoặc dải 3.3V - 6V vào chân `5V` trên mạch.
    
- **Ổn áp:** Tích hợp LDO hạ áp xuống 3.3V (chịu tải tối đa khoảng 500mA).
    
- **Deep Sleep:** Dòng rò cực thấp (~43µA), phù hợp làm thiết bị IoT chạy pin.
    

## 2. Sơ Đồ Chân (Pinout)
![[ESP32-C3-Super-Mini-Pinout-2025.svg|535]]
Mạch gồm 16 chân chia làm 2 hàng. Nhìn từ trên xuống, cổng USB-C hướng lên:

### Hàng bên trái (Nguồn và ADC)

- **5V:** Cấp nguồn vào 5V hoặc ngõ ra 5V (nếu đang cắm USB).
    
- **GND:** Chân nối đất.
    
- **3V3:** Nguồn ra 3.3V (từ LDO).
    
- **IO0 -> IO3:** GPIO đa năng, hỗ trợ ADC1.
    
- **IO4:** GPIO / ADC1 / Thường dùng làm SCK của SPI.
    

### Hàng bên phải (Giao tiếp)

- **IO5 -> IO7:** GPIO / Thường map với SPI (MISO, MOSI, SS).
    
- **IO8:** Điều khiển LED xanh dương trên mạch (Active Low).
    
- **IO9:** Nút nhấn BOOT.
    
- **IO10:** GPIO đa năng.
    
- **IO20 (RX) / IO21 (TX):** Giao tiếp UART (Serial phần cứng).
    
