# Remote Serial Monitor (ESP32 - Web)

Hệ thống giám sát và điều khiển Serial từ xa qua giao diện Web, sử dụng Node.js và SQLite Native.

## 🚀 Tính năng
- **Real-time Monitoring**: Xem log từ ESP32 theo thời gian thực với độ trễ cực thấp (Polling 500ms).
- **Remote Control**: Gửi lệnh (AT Commands) tới ESP32 từ bất kỳ trình duyệt nào.
- **Modern Tech Stack**: Sử dụng Node.js 22+, SQLite Native (không cần thư viện ngoài), Docker Compose.
- **Auto-scroll & Color-coded**: Giao diện Dark Mode, tự động cuộn và phân loại màu sắc log (Lệnh, Phản hồi, Dữ liệu).
- **Data Persistence**: Dữ liệu được bảo toàn an toàn trong Docker Volume.

## 🛠 Cấu trúc dự án
- `ai_studio_code.js`: Backend API & SQLite Logic.
- `ai_studio_code.html`: Frontend giao diện người dùng.
- `Dockerfile`: Cấu hình môi trường Node 22 Alpine.
- `docker-compose.yml`: Quản lý container và volume.

## 📦 Hướng dẫn triển khai nhanh

### Yêu cầu
- Đã cài đặt [Docker](https://docs.docker.com/get-docker/) và [Docker Compose](https://docs.docker.com/compose/install/).

### Các bước thực hiện
1. **Tải mã nguồn:**
   ```bash
   git clone https://github.com/VoThLong/Global_Star.git
   cd Web
   ```

2. **Khởi chạy bằng Docker Compose:**
   ```bash
   docker compose up -d --build
   ```

3. **Truy cập giao diện:**
   Mở trình duyệt và truy cập: `http://localhost:3000`

## 🔌 Kết nối với ESP32
ESP32 của bạn cần tương tác với các Endpoints sau:
- **Lấy lệnh mới (Poll):** `GET http://<SERVER_IP>:3000/command`
- **Gửi dữ liệu lên:** `POST http://<SERVER_IP>:3000/upload` (Body: `{"data": "nội dung log"}`)

## 💾 Quản lý dữ liệu
Dữ liệu được lưu trong Docker Volume. Để copy file database ra máy cục bộ, sử dụng lệnh:
```bash
docker cp serial-monitor:/app/data/logs.db ./logs.db
```

## 📝 Giấy phép
Dự án được phát hành dưới giấy phép ISC.
