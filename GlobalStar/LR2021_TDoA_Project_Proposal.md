# [RESEARCH PROPOSAL] ASSETS TRACKING & INDOOR LOCALIZATION: THE NEXT-GEN LORA-BASED TDOA

**Tên dự án gợi ý:** **"Next-Gen Asset Tracking using LR2021 Multi-band TDoA/RTToF"**
*(Định vị tài sản dựa trên công nghệ LoRa thế hệ mới)*

**Đơn vị:** Nhóm Nghiên cứu **The Things Lab (TTLab)** – Khoa KTMT, UIT.
**Đối tượng:** Sinh viên năm 2 (Chương trình chính quy/CLC/Tiên tiến), Khoa KTMT.

---

## 1. GIỚI THIỆU (INTRODUCTION)

Trong kỷ nguyên IoT, việc theo dõi tài sản (Assets Tracking) trong nhà và các nhà kho thông minh đòi hỏi sự cân bằng giữa: **Khoảng cách truyền - Công suất tiêu thụ - Độ chính xác**. Các công nghệ hiện nay như WiFi/BLE có độ chính xác thấp, trong khi UWB (như Apple AirTag) dù rất chính xác nhưng tầm xa cực ngắn và chi phí triển khai cao.

Sự xuất hiện của **Semtech LR2021 (LoRa Plus™)** đã thay đổi cuộc chơi. Với IP thế hệ thứ 4, LR2021 không chỉ truyền tin xa hàng kilomet mà còn tích hợp **Ranging Engine** tiên tiến. Dự án tại **TTLab** sẽ tập trung khai phá khả năng định vị dựa trên **TDoA (Time Difference of Arrival)** và **RTToF**, nhằm tạo ra một hệ thống định vị nội khu có tầm phủ sóng rộng nhưng vẫn đạt độ chính xác ở cấp độ mét.

---

## 2. CƠ SỞ LÝ THUYẾT VÀ CÔNG NGHỆ (TECHNOLOGY FOUNDATION)

### 2.1. Tại sao lại là LR2021?
LR2021 vượt trội hơn các thế hệ SX1280 hay LR1110 nhờ khả năng hoạt động đa băng tần (**Sub-GHz và 2.4 GHz**). Điều này cho phép hệ thống:
* **Tận dụng băng tần Sub-GHz:** Để xuyên vật cản tốt hơn trong môi trường công nghiệp.
* **Tận dụng băng tần 2.4 GHz:** Để đạt băng thông (BW) lớn, từ đó tăng độ phân giải thời gian.

### 2.2. Nguyên lý Định vị TDoA & RTToF
Dự án sẽ nghiên cứu sự kết hợp giữa hai phương pháp chính:
* **RTToF (Round Trip Time of Flight):** Đo thời gian khứ hồi giữa Tag và Anchor để xác định khoảng cách chính xác mà không cần đồng bộ hóa xung nhịp cực khắt khe giữa các trạm.
* **TDoA (Time Difference of Arrival):** Xác định vị trí dựa trên sự chênh lệch thời gian tín hiệu đến các Gateway khác nhau. 
* **Công thức cốt lõi:** Sai số khoảng cách $\Delta d$ phụ thuộc trực tiếp vào Băng thông (BW):
$$D_{LSB} = \frac{c}{2^{12} \times BW}$$
*Với LR2021, việc mở rộng BW và thuật toán xử lý pha mới giúp giảm thiểu nhiễu đa đường (Multipath) – kẻ thù số 1 của định vị trong nhà.*

---

## 3. PHẠM VI DỰ ÁN - GIAI ĐOẠN 1 (PROJECT SCOPE)

Giai đoạn đầu tập trung vào thực nghiệm và đánh giá khách quan (Benchmarking):
1.  **Đo đạc môi trường LOS (Line-of-Sight):** Đánh giá sai số lý tưởng của LR2021 trong điều kiện không vật cản.
2.  **Đo đạc môi trường NLOS (Non-Line-of-Sight):** Thử nghiệm tại hành lang, phòng Lab E6.1 với nhiều vật cản để đánh giá khả năng xuyên thấu và xử lý đa đường.
3.  **So sánh đối chứng (Competitive Analysis):**
    * **vs. SX1280/LR1110:** Để thấy sự cải tiến của Generation 4 LoRa IP.
    * **vs. UWB (Apple AirTag):** So sánh giữa một bên là "Độ chính xác tuyệt đối - Tầm ngắn" (UWB) và một bên là "Độ chính xác khá - Tầm xa - Năng lượng cực thấp" (LR2021).

---

## 4. QUY TRÌNH TUYỂN CHỌN & LỢI ÍCH

### 4.1. Quy trình tuyển chọn
Đơn giản và tập trung vào tiềm năng:
* **Ứng tuyển:** Sinh viên nộp **CV** (tóm tắt thông tin cá nhân, các môn đã học, điểm trung bình và các dự án nhỏ đã tham gia nếu có).
* **Phỏng vấn:** Lab sẽ liên hệ phỏng vấn trực tiếp để trao đổi về đam mê và định hướng nghiên cứu.

### 4.2. Lợi ích khi tham gia TTLab

**Tiếp cận công nghệ mới nhất**: LR2021 hiện là dòng chip "state-of-the-art" của Semtech, rất ít Lab tại Việt Nam có sẵn kit để thử nghiệm.

**Hướng dẫn từ chuyên gia**: Được hướng dẫn trực tiếp bởi các giảng viên và anh chị khóa trên (Senior) có kinh nghiệm về RF.

**Cơ hội công bố khoa học**: Các dữ liệu so sánh (Benchmarking) từ dự án có khả năng phát triển thành bài báo đăng tại các hội nghị sinh viên như IEEE RIVF hoặc Hội nghị sinh viên nghiên cứu khoa học UIT.

**Chuẩn bị cho Khóa luận tốt nghiệp**: Đây là bước đệm hoàn hảo để hình thành đề tài khóa luận năm cuối về Smart City hoặc IoT.

---

**Liên hệ nộp CV:** [Email Giảng viên/Trưởng Lab]
**Địa điểm làm việc:** The Things Lab (TTLab) – Khoa KTMT, UIT.

*Hãy tham gia cùng chúng tôi để định nghĩa lại tương lai của Asset Tracking!*