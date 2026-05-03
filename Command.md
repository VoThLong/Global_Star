# Tài liệu AT Command - Realm Edge Application Platform API

## Tổng quan

Tài liệu này tổng hợp toàn bộ các lệnh AT, cú pháp, tham số, phản hồi và mã lỗi từ tài liệu "Realm Edge Application Platform API Manual" (Mã: 8550-0002-01 R-7) của Globalstar. Các lệnh được sắp xếp theo nhóm chức năng.

**Quy ước:**
- `<tham_số>`: Giá trị cần nhập
- `[tham_số]`: Tham số tùy chọn
- Phản hồi thành công: `OK`
- Phản hồi thất bại: `+ERROR: <mã_lỗi>`

---

## Mã lỗi trả về chuẩn

| Mã lỗi | Tên | Mô tả |
|--------|-----|-------|
| 0 | OK | Thành công |
| 1 | INVALID_PARAMS | Tham số không hợp lệ |
| 2 | BUFFER_FULL | Bộ đệm đầy |
| 3 | CANNOT_ABORT | Không thể hủy lệnh/tác vụ |
| 4 | HARDWARE_ERROR | Lỗi phần cứng |
| 5 | DEVICE_DISABLED | Thiết bị bị vô hiệu hóa |
| 6 | DEVICE_DEACTIVATED | Thiết bị chưa kích hoạt dịch vụ |
| 7 | ALREADY_QUEUED | Tin nhắn/tác vụ đã tồn tại trong hàng đợi |
| 8 | LOCATION_UNAVAILABLE | Không thể lấy vị trí GPS |
| 9 | ALREADY_IN_SESSION | Thiết bị đang trong phiên làm việc khác |
| 10 | RESOURCE_ERROR | Lỗi tài nguyên hệ thống |
| 11 | NOT_FOUND | Không tìm thấy đối tượng/ID |
| 12 | BAD_STATE | Thiết bị ở sai trạng thái |
| 13 | ALREADY_EXISTS | Đối tượng đã tồn tại |
| 14 | PERMISSION_ERROR | Không có quyền thực thi |
| 15 | TX_LIFETIME_EXPIRED | Hết thời gian chờ truyền tin |
| 22 | BUSY | Hệ thống đang bận |
| 23 | TX_QUEUE_EMPTY | Hàng đợi phát trống |
| 24 | BUFFER_EMPTY | Bộ đệm trống |

---

## 1. Lệnh cấu hình hệ thống

### AT+COMMIT

**Mô tả:** Lưu (commit) các thay đổi cấu hình vào bộ nhớ flash không bay hơi.

**Cú pháp:**
```
AT+COMMIT
```

**Phản hồi:**
```
OK
```
Hoặc nếu có lỗi:
```
+ERROR: <mã_lỗi>
```

---

### AT+FACTORYRESET

**Mô tả:** Khôi phục thiết bị về trạng thái cài đặt gốc. Hỗ trợ hai loại reset: `0` - reset về mặc định không khởi động lại, `1` - reset và khởi động lại.

**Cú pháp:**
```
AT+FACTORYRESET=<config_reset_type_enum>
```

**Tham số:**
- `config_reset_type_enum`: `0` = CONFIG_RESET, `1` = CONFIG_RESET_WITH_REBOOT

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+CFGVER

**Mô tả:** Đọc hoặc cài đặt phiên bản cấu hình (major.minor). Nếu đặt thành "0.0", thiết bị ở trạng thái xuất xưởng và sẽ tự tắt nguồn sau vài giây.

**Cú pháp đọc:**
```
AT+CFGVER?
```

**Phản hồi đọc:**
```
+CFGVER: <major.minor>
OK
```

**Cú pháp ghi:**
```
AT+CFGVER=<major.minor>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+CFGGETERRPRESENT

**Mô tả:** Kiểm tra thiết bị có đang gặp lỗi phần cứng hoặc lỗi khởi tạo cấu hình không.

**Cú pháp:**
```
AT+CFGGETERRPRESENT?
```

**Phản hồi:**
```
+CFGGETERRPRESENT: 0   (0 = không lỗi)
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+CFGPFNAME

**Mô tả:** Đọc hoặc đặt tên Profile cấu hình. Để trống hoặc "DEFAULT" để ở trạng thái xuất xưởng.

**Cú pháp đọc:**
```
AT+CFGPFNAME?
```

**Phản hồi đọc:**
```
+CFGPFNAME: <tên_profile>
OK
```

**Cú pháp ghi:**
```
AT+CFGPFNAME=<tên_profile>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+DEVINITSTATUS

**Mô tả:** Trả về trạng thái khởi tạo của tất cả thành phần và các lỗi liên quan.

**Cú pháp:**
```
AT+DEVINITSTATUS?
```

**Phản hồi:**
```
+DEVINITSTATUS: <0xfaultstat>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

## 2. Lệnh bảo mật

### AT+AUTHPW

**Mô tả:** Đặt mật khẩu ủy quyền cho phép thực thi lệnh cấu hình. Chỉ truy cập qua giao diện BLE config. Độ dài chuỗi mật khẩu: 1-17 ký tự ASCII.

**Cú pháp đọc:**
```
AT+AUTHPW?
```

**Phản hồi đọc:**
```
+AUTHPW: <mật_khẩu>
OK
```

**Cú pháp ghi:**
```
AT+AUTHPW=<mật_khẩu>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+SECAUH

**Mô tả:** Yêu cầu nâng cao quyền ủy quyền trên giao diện hiện tại.

**Cú pháp đọc:**
```
AT+SECAUH?
```

**Phản hồi đọc:**
```
+SECAUH: <gstar_security_policy_t>
OK
```

**Cú pháp ghi:**
```
AT+SECAUH=<enable>,<mật_khẩu>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+SECAUHVL

**Mô tả:** Đặt chính sách bảo mật cho các giao diện cấu hình (UART, NUS).

**Cú pháp đọc:**
```
AT+SECAUHVL?
```

**Phản hồi đọc:**
```
+SECAUHVL: <config_security_entry_type_enum>,<authTimeoutSeconds>
...
OK
```

**Cú pháp ghi:**
```
AT+SECAUHVL=<config_security_entry_type_enum>,<gstar_security_policy_type_t>,<authTimeoutSeconds>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+UARTSEC

**Mô tả:** Đặt chính sách bảo mật cho giao diện UART.

**Cú pháp đọc:**
```
AT+UARTSEC?
```

**Phản hồi đọc:**
```
+UARTSEC: <gstar_security_thread_type_t>,<authTimeoutSeconds>
OK
```

**Cú pháp ghi:**
```
AT+UARTSEC=<gstar_security_policy_type_t>,<authTimeoutSeconds>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+NUSSEC

**Mô tả:** Đặt chính sách bảo mật cho giao diện NUS.

**Cú pháp đọc:**
```
AT+NUSSEC?
```

**Phản hồi đọc:**
```
+NUSSEC: <gstar_security_thread_type_t>,<authTimeoutSeconds>
OK
```

**Cú pháp ghi:**
```
AT+NUSSEC=<gstar_security_policy_type_t>,<authTimeoutSeconds>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+USBSEC

**Mô tả:** Đặt chính sách bảo mật cho giao diện USB.

**Cú pháp đọc:**
```
AT+USBSEC?
```

**Phản hồi đọc:**
```
+USBSEC: <gstar_security_thread_type_t>,<authTimeoutSeconds>
OK
```

**Cú pháp ghi:**
```
AT+USBSEC=<gstar_security_policy_type_t>,<authTimeoutSeconds>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

## 3. Lệnh định danh & thông tin thiết bị

### AT+CGMI

**Mô tả:** Yêu cầu tên nhà sản xuất thiết bị.

**Cú pháp:**
```
AT+CGMI?
```

**Phản hồi:**
```
+CGMI: Globalstar
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+CGMM

**Mô tả:** Yêu cầu thông tin model thiết bị (VD: ST150).

**Cú pháp:**
```
AT+CGMM?
```

**Phản hồi:**
```
+CGMM: <tên_device>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+CGMR

**Mô tả:** Đọc chi tiết phiên bản phần mềm của từng thành phần.

**Cú pháp:**
```
AT+CGMR?
```

**Phản hồi:**
```
+CGMR: <nordic_version>,<soft_device_version>,<asic_version>,<bootloader_version>,<agg_version>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GUID

**Mô tả:** Lấy mã UID của thiết bị.

**Cú pháp:**
```
AT+GUID?
```

**Phản hồi:**
```
+GUID: <xxxxxxxxxxxx>
OK
```

---

### AT+CGSN

**Mô tả:** Lấy số ESN của thiết bị.

**Cú pháp:**
```
AT+CGSN?
```

**Phản hồi:**
```
+CGSN: <x-xxxxxxx>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+BDREV

**Mô tả:** Đọc phiên bản bo mạch (Board Revision).

**Cú pháp:**
```
AT+BDREV?
```

**Phản hồi:**
```
+BDREV: <d.d>
OK
```

---

### AT+ASYREV

**Mô tả:** Đọc phiên bản lắp ráp (Assembly Revision).

**Cú pháp:**
```
AT+ASYREV?
```

**Phản hồi:**
```
+ASYREV: <d.d>
OK
```

---

### AT+HWREV

**Mô tả:** Đọc phiên bản phần cứng (Hardware Revision).

**Cú pháp:**
```
AT+HWREV?
```

**Phản hồi:**
```
+HWREV: <d.d>
OK
```

---

### AT+MECREV

**Mô tả:** Đọc phiên bản cơ khí (Mechanical Revision).

**Cú pháp:**
```
AT+MECREV?
```

**Phản hồi:**
```
+MECREV: <d.d>
OK
```

---

### AT+PDSKUREV

**Mô tả:** Đọc mã SKU sản phẩm.

**Cú pháp:**
```
AT+PDSKUREV?
```

**Phản hồi:**
```
+PDSKUREV: <xxxxxxx>
OK
```

---

### AT+HWSKUREV

**Mô tả:** Đọc mã SKU phần cứng.

**Cú pháp:**
```
AT+HWSKUREV?
```

**Phản hồi:**
```
+HWSKUREV: <xxxxxxx>
OK
```

---

### AT+DEVMFGD

**Mô tả:** Đọc ngày sản xuất thiết bị.

**Cú pháp:**
```
AT+DEVMFGD?
```

**Phản hồi:**
```
+DEVMFGD: <tháng>,<ngày>,<năm>
OK
```

---

### AT+DEVAGGVER

**Mô tả:** Đọc hoặc ghi phiên bản tổng hợp (Aggregated Revision).

**Cú pháp đọc:**
```
AT+DEVAGGVER?
```

**Phản hồi đọc:**
```
+DEVAGGVER: <major>,<minor>,<rc_rev>
OK
```

**Cú pháp ghi:**
```
AT+DEVAGGVER=<major>,<minor>,<rc_rev>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

## 4. Điều khiển thu phát sóng (Transmitter / Transceiver)

### AT+TXACTS

**Mô tả:** Kiểm tra trạng thái kích hoạt bộ phát (đã kích hoạt qua app hay đã hết hạn).

**Cú pháp:**
```
AT+TXACTS?
```

**Phản hồi:**
```
+TXACTS: <trạng_thái>,[<ngày>,<tháng>,<năm>]
OK
```

---

### AT+TCSM

**Mô tả:** Đọc/Ghi chế độ chọn kênh tần số phát (Tự động theo GPS hoặc Chỉnh tay).

**Cú pháp đọc:**
```
AT+TCSM?
```

**Phản hồi đọc:**
```
+TCSM: <mã_chế_độ>
OK
```

**Cú pháp ghi:**
```
AT+TCSM=<tx_channel_select_mode_enum>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+CFDC

**Mô tả:** Đọc/Ghi kênh phát cụ thể (A, B hoặc C) khi ở chế độ chỉnh tay.

**Cú pháp đọc:**
```
AT+CFDC?
```

**Phản hồi đọc:**
```
+CFDC: <tx_channel_enum>
OK
```

**Cú pháp ghi:**
```
AT+CFDC=<tx_channel_enum>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+TXTEMPE

**Mô tả:** Đọc trạng thái lỗi nhiệt độ bộ phát.

**Cú pháp:**
```
AT+TXTEMPE?
```

**Phản hồi:**
```
+TXTEMPE: <bool>
OK
```

---

### AT+TXTEMPERREN

**Mô tả:** Bật/tắt lỗi nhiệt độ bộ phát (ngăn truyền khi quá nhiệt hoặc dưới nhiệt độ).

**Cú pháp đọc:**
```
AT+TXTEMPERREN?
```

**Phản hồi đọc:**
```
+TXTEMPERREN: <bool>
OK
```

**Cú pháp ghi:**
```
AT+TXTEMPERREN=<enabled>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+TXUNTEMPERREN

**Mô tả:** Bật/tắt lỗi dưới nhiệt độ bộ phát.

**Cú pháp đọc:**
```
AT+TXUNTEMPERREN?
```

**Phản hồi đọc:**
```
+TXUNTEMPERREN: <bool>
OK
```

**Cú pháp ghi:**
```
AT+TXUNTEMPERREN=<enabled>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+TXMITONOFF

**Mô tả:** Bật (1) hoặc Tắt (0) cưỡng bức nguồn điện module phát sóng.

**Cú pháp đọc:**
```
AT+TXMITONOFF?
```

**Phản hồi đọc:**
```
+TXMITONOFF: <bool>
OK
```

**Cú pháp ghi:**
```
AT+TXMITONOFF=<on>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+RASE

**Mô tả:** Đọc trạng thái ngoại lệ RAS.

**Cú pháp:**
```
AT+RASE?
```

**Phản hồi:**
```
+RASE: <ras_area_exception>,<ras_excluded_area>,<indicated_channel>
OK
```

---

### AT+TXNSF

**Mô tả:** Cấu hình cờ thông báo URC cho bộ phát.

**Cú pháp đọc:**
```
AT+TXNSF?
```

**Phản hồi đọc:**
```
+TXNSF: <transmitterNotifyFlags>
OK
```

**Cú pháp ghi:**
```
AT+TXNSF=<transmitterNotifyFlags>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+TXRXNSF

**Mô tả:** Cấu hình cờ thông báo URC cho bộ thu/phát (Transceiver).

**Cú pháp đọc:**
```
AT+TXRXNSF?
```

**Phản hồi đọc:**
```
+TXRXNSF: <transceiverNotifyFlags>
OK
```

**Cú pháp ghi:**
```
AT+TXRXNSF=<transceiverNotifyFlags>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+MODEMBUSY

**Mô tả:** Bật/tắt trạng thái bận modem để cập nhật firmware modem mà không bị gián đoạn.

**Cú pháp đọc:**
```
AT+MODEMBUSY?
```

**Phản hồi đọc:**
```
+MODEMBUSY: <0/1>
OK
```

**Cú pháp ghi:**
```
AT+MODEMBUSY=<0/1>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+RXDIAGMODE

**Mô tả:** Đặt bộ thu vào chế độ chẩn đoán.

**Cú pháp:**
```
AT+RXDIAGMODE=<time_s>
```

**Tham số:**
- `time_s`: 16-bit unsigned, 65535 không hợp lệ.

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+MUSERRESET

**Mô tả:** Reset tất cả cài đặt modem về mặc định xuất xưởng.

**Cú pháp:**
```
AT+MUSERRESET
```

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+QUICKFLACK

**Mô tả:** Chọn giữa ACK định thời (timed) hoặc ACK nhanh (quick).

**Cú pháp đọc:**
```
AT+QUICKFLACK?
```

**Phản hồi đọc:**
```
+QUICKFLACK: <1 or 0>
```
(1 = dùng timer, 0 = quick ACK)

**Cú pháp ghi:**
```
AT+QUICKFLACK=<1 or 0>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+FLACKDELAY

**Mô tả:** Đặt độ trễ FLACK (Forward Link ACK) tính bằng giây.

**Cú pháp đọc:**
```
AT+FLACKDELAY?
```

**Phản hồi đọc:**
```
+FLACKDELAY: <delay_giây>
```

**Cú pháp ghi:**
```
AT+FLACKDELAY=<delay_giây>
```
Mặc định: 30 giây. Khoảng: 10-30 giây.

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+MGPSTIMESYNC

**Mô tả:** Bật/tắt đồng bộ thời gian GPS giữa Nordic và Modem.

**Cú pháp đọc:**
```
AT+MGPSTIMESYNC?
```

**Phản hồi đọc:**
```
+MGPSTIMESYNC: <0/1>
```

**Cú pháp ghi:**
```
AT+MGPSTIMESYNC=<enable>
```
`enable` = 1 (bật, mặc định), 0 (tắt)

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

## 5. Quản lý hàng đợi và gửi bản tin

### AT+QCNT

**Mô tả:** Truy vấn số lượng bản tin trong hàng đợi.

**Cú pháp:**
```
AT+QCNT?
```

**Phản hồi:**
```
+QCNT: <n>
OK
```

---

### AT+QSIZE

**Mô tả:** Truy vấn tổng kích thước bộ nhớ hàng đợi.

**Cú pháp:**
```
AT+QSIZE?
```

**Phản hồi:**
```
+QSIZE: <n>
OK
```

---

### AT+QILBCNTR

**Mô tả:** Thiết lập bộ đếm xen kẽ (Interleave Count) - số tin nhắn tối đa truyền trong 1 chu kỳ.

**Cú pháp đọc:**
```
AT+QILBCNTR?
```

**Phản hồi đọc:**
```
+QILBCNTR: <n>
OK
```

**Cú pháp ghi:**
```
AT+QILBCNTR=<n>
```
`n` = 1 (tắt interleaving) hoặc 10 (bật)

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+QMPR

**Mô tả:** Đọc tóm tắt bản tin đang chờ gửi.

**Cú pháp:**
```
AT+QMPR?
```

**Phản hồi:**
```
+QMPR: <priority>,<queueID>,<tx_ready>,<num_send_attempts>,<num_remaining>,<type>,<sub_type>,<mod_msg_type>,<data_len>,<unix_ts>,<error_exception>,<umn>,<ack_msg_type>,<burst_timestamp>
OK
```

---

### AT+QMD

**Mô tả:** Đọc chi tiết toàn bộ nội dung bản tin theo queue_id.

**Cú pháp:**
```
AT+QMD=<queue_id>
```

**Phản hồi:**
```
+QMD: <priority>,<queueID>,<tx_ready>,<num_send_attempts>,<num_remaining>,<type>,<sub_type>,<mod_msg_type>,<data_len>,<unix_ts>,<error_exception>,<data>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+QABORT

**Mô tả:** Hủy/Xóa một bản tin cụ thể bằng Queue ID.

**Cú pháp:**
```
AT+QABORT=<queue_id>
```

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+QABORTALL

**Mô tả:** Xóa/Hủy toàn bộ các bản tin đang trong hàng đợi.

**Cú pháp:**
```
AT+QABORTALL
```

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+QPS

**Mô tả:** Cấu hình chế độ preemption cho hàng đợi.

**Cú pháp đọc:**
```
AT+QPS?
```

**Phản hồi đọc:**
```
+QPS: <queue_preempt_settings_enum>
OK
```

**Cú pháp ghi:**
```
AT+QPS=<queue_preempt_settings_enum>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

**Các giá trị:**
- `0`: Preemption disabled
- `1`: Preemption by priority
- `2`: Preemption by time
- `3`: Preemption by priority and time

---

### AT+QNSF

**Mô tả:** Cấu hình cờ thông báo URC cho hàng đợi.

**Cú pháp đọc:**
```
AT+QNSF?
```

**Phản hồi đọc:**
```
+QNSF: <messageQueueNotifyFlags>
OK
```

**Cú pháp ghi:**
```
AT+QNSF=<messageQueueNotifyFlags>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+RSEND

**Mô tả:** Thêm bản tin dữ liệu thô (Raw) vào hàng đợi phát.

**Cú pháp:**
```
AT+RSEND=<u8_msg_priority>,<u8_data_length>,<data>
```

**Tham số:**
- `u8_msg_priority`: 1-3
- `u8_data_length`: 1-144
- `data`: chuỗi hex

**Phản hồi:**
```
+RSEND: <queue_id>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+RBLESEND

**Mô tả:** Thêm bản tin cảm biến BLE thô vào hàng đợi phát.

**Cú pháp:**
```
AT+RBLESEND=<subtype>,<u8_msg_priority>,<u8_data_length>,<data>
```

**Tham số:**
- `subtype`: 1 = loại 59, 2 = loại 63
- `u8_msg_priority`: 1-3
- `u8_data_length`: 1-143
- `data`: chuỗi hex

**Phản hồi:**
```
+RBLESEND: <queue_id>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+HSEND

**Mô tả:** Thêm bản tin kiểm tra sức khỏe (Health Check) vào hàng đợi.

**Cú pháp:**
```
AT+HSEND
```

**Phản hồi:**
```
+HSEND: <queue_id>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+STDSEND

**Mô tả:** Gửi một "Tin nhắn Chuẩn" (Standard Message).

**Cú pháp:**
```
AT+STDSEND=<ota_type0_subtype>,<withgps>,[<inputtrigger>]
```

**Tham số:**
- `ota_type0_subtype`: 0 = Normal, 1 = Power On, 2 = COL, 3 = Input Change, 4 = Undesired, 5 = Recenter
- `withgps`: 1 có GPS, 0 không GPS
- `inputtrigger`: 1=DC1, 2=DC2, 3=vibration (cho subtype 3 hoặc 4)

**Phản hồi:**
```
+STDSEND: <queue_id>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+SHSEND

**Mô tả:** Gửi tin nhắn chứa thông tin Tốc độ và Hướng di chuyển.

**Cú pháp:**
```
AT+SHSEND=<withgps>
```
`withgps`: 1 (có GPS), 0 (không GPS)

**Phản hồi:**
```
+SHSEND: <queue_id>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+ACSEND

**Mô tả:** Gửi bản tin Đếm/Tích lũy (Accumulate/Count) vào hàng đợi.

**Cú pháp:**
```
AT+ACSEND
```

**Phản hồi:**
```
+ACSEND: <queue_id>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+RASEND

**Mô tả:** Gửi bản tin thô (Raw) có yêu cầu xác nhận ACK (chỉ RS200M).

**Cú pháp:**
```
AT+RASEND=<u8_msg_priority>,<u8_data_length>,<data>
```

**Tham số:**
- `u8_msg_priority`: 1-3
- `u8_data_length`: 1-141

**Phản hồi:**
```
+RASEND: <queue_id>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+TASEND

**Mô tả:** Gửi bản tin rút gọn (Truncated) có ACK (chỉ RS200M).

**Cú pháp:**
```
AT+TASEND=<u8_msg_priority>,<u8_data_length>,<data>
```

**Tham số:**
- `u8_msg_priority`: 1-3
- `u8_data_length`: 1-134

**Phản hồi:**
```
+TASEND: <queue_id>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+TYPE3MSGACK

**Mô tả:** Bật/tắt xác nhận cho loại tin nhắn Type 3 (RM200).

**Cú pháp đọc:**
```
AT+TYPE3MSGACK?
```

**Phản hồi đọc:**
```
+TYPE3MSGACK: <enabled>
OK
```

**Cú pháp ghi:**
```
AT+TYPE3MSGACK=<ack_enabled>
```
`ack_enabled`: 0 hoặc 1

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+RDBS

**Mô tả:** Đọc/Ghi cấu hình burst cho tin nhắn Raw theo mức ưu tiên.

**Cú pháp đọc:**
```
AT+RDBS?
```

**Phản hồi đọc:**
```
+RDBS: <priority>,<burst_count>,<min_interval_seconds>,<max_interval_seconds>
... (cho priority 1,2,3)
OK
```

**Cú pháp ghi:**
```
AT+RDBS=<message_priority>,<burst_count>,<min_interval_seconds>,<max_interval_seconds>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+TDBS

**Mô tả:** Đọc/Ghi cấu hình burst cho tin nhắn Truncated.

**Cú pháp đọc:**
```
AT+TDBS?
```

**Phản hồi đọc:**
```
+TDBS: <priority>,<burst_count>,<min_interval_seconds>,<max_interval_seconds>
...
OK
```

**Cú pháp ghi:**
```
AT+TDBS=<message_priority>,<burst_count>,[<min_interval_seconds>,<max_interval_seconds>]
```

**Phản hồi ghi:**
```
+TDBS: <priority>,<burst_count>,<min_interval_seconds>,<max_interval_seconds>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+TOMS

**Mô tả:** Chọn loại OTA cho tin nhắn Truncated.

**Cú pháp đọc:**
```
AT+TOMS?
```

**Phản hồi đọc:**
```
+TOMS: <truncated_msg_ota_type_enum>
OK
```

**Cú pháp ghi:**
```
AT+TOMS=<truncated_msg_ota_type_enum>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+TSEND

**Mô tả:** Gửi tin nhắn Truncated Data (có GPS).

**Cú pháp:**
```
AT+TSEND=<u8_msg_priority>,<u8_data_length>,<data>
```

**Phản hồi:**
```
+TSEND: <queue_id>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+TBLSEND

**Mô tả:** Gửi tin nhắn cảm biến Truncated Data (BLE sensor).

**Cú pháp:**
```
AT+TBLSEND=<subtype>,<u8_msg_priority>,<u8_data_length>,<data>
```
`subtype`: 1 = type 59, 2 = type 63

**Phản hồi:**
```
+TBLSEND: <queue_id>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+OTAMSGGET / AT+OTAMSGSET

**Mô tả:** Đọc/Ghi thông số cấu hình cho các loại tin nhắn OTA (độ ưu tiên, khoảng thời gian, số lần gửi lại).

**Cú pháp đọc:**
```
AT+OTAMSGGET=<type>,<subtype>,[<messagePriority>],[<mod_msg_type>]
```

**Phản hồi đọc:**
```
+OTAMSGGET: <type>,<sub_type>,<mod_msg_type>,<priority>,<burstCount>,<minIntervalSeconds>,<maxIntervalSeconds>
OK
```

**Cú pháp ghi:**
```
AT+OTAMSGSET=<type>,<sub_type>,<messagePriority>,<burstCount>,<minIntervalSeconds>,<maxIntervalSeconds>,[<mod_msg_type>]
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+PRWONDATA

**Mô tả:** Cài đặt chuỗi dữ liệu tự động gửi đi ngay khi thiết bị khởi động.

**Cú pháp đọc:**
```
AT+PRWONDATA?
```

**Phản hồi đọc:**
```
+PRWONDATA: <hexStr>
OK
```

**Cú pháp ghi:**
```
AT+PRWONDATA=<payload_length>,<hexbuff>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+CFGMODMSG

**Mô tả:** Cấu hình Modular Message.

**Cú pháp đọc:**
```
AT+CFGMODMSG?
```

**Phản hồi đọc:**
```
+CFGMODMSG: <msg_type>,<config_byte>
...
OK
```

**Cú pháp ghi:**
```
AT+CFGMODMSG=<msg_type>,<config_byte>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

## 6. Định vị GPS & Hàng rào địa lý

### AT+GPSSTAT

**Mô tả:** Đọc/ghi trạng thái GPS (Disabled, Internal, Manual).

**Cú pháp đọc:**
```
AT+GPSSTAT?
```

**Phản hồi đọc:**
```
+GPSSTAT: <gps_status_enum>
OK
```

**Cú pháp ghi:**
```
AT+GPSSTAT=<gps_status_enum>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GPSPOS

**Mô tả:** Đọc vị trí GPS hiện tại.

**Cú pháp:**
```
AT+GPSPOS?
```

**Phản hồi:**
```
+GPSPOS: <year>,<month>,<day>,<hour>,<minute>,<second>,<millisecond>,<lat>,<lon>,<heading>,<speed>,<altitude>,<hdop>,<vdop>,<is_3D>,<hor_accuracy>,<ver_accuracy>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GPSSAT

**Mô tả:** Đọc thông tin vệ tinh GPS hiện tại.

**Cú pháp:**
```
AT+GPSSAT?
```

**Phản hồi:**
```
+GPSSAT: <sat_id>,<elevation>,<azimuth>,<cn0>
...
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GPSLPOS

**Mô tả:** Đọc danh sách vị trí GPS đã lưu trong quá khứ.

**Cú pháp:**
```
AT+GPSLPOS=<maxPositions>
```

**Phản hồi:**
```
+GPSLPOS: <year>,<month>,<day>,<hour>,<minute>,<second>,<millisecond>,<lat>,<lon>,<heading>,<speed>,<altitude>,<hdop>,<vdop>,<is_3d>,<hor_accuracy>,<ver_accuracy>
...
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GPSLSAT

**Mô tả:** Đọc thông tin vệ tinh GPS đã lưu trước đó.

**Cú pháp:**
```
AT+GPSLSAT?
```

**Phản hồi:**
```
+GPSLSAT: <sat_id>,<elevation>,<azimuth>,<cn0>
...
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GPSGPOS

**Mô tả:** Xác định tọa độ GPS làm tâm của hàng rào địa lý.

**Cú pháp đọc:**
```
AT+GPSGPOS?
```

**Phản hồi đọc:**
```
+GPSGPOS: <lat>,<lon>
OK
```

**Cú pháp ghi:**
```
AT+GPSGPOS=<lat>,<lon>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GEOSETTINGS

**Mô tả:** Định nghĩa hình dạng hàng rào địa lý (0=Vuông, 1=Tròn) và kích thước (mét).

**Cú pháp đọc:**
```
AT+GEOSETTINGS?
```

**Phản hồi đọc:**
```
+GEOSETTINGS: <geo_shape>,<geo_distance_m>
OK
```

**Cú pháp ghi:**
```
AT+GEOSETTINGS=<geo_shape>,<geo_distance_m>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GPSTPOS

**Mô tả:** Đọc vị trí GPS liên quan đến lần truyền cuối cùng.

**Cú pháp:**
```
AT+GPSTPOS?
```

**Phản hồi:**
```
+GPSTPOS: <year>,<month>,<day>,<hour>,<minute>,<second>,<millisecond>,<lat>,<lon>,<heading>,<speed>,<altitude>,<hdop>,<vdop>,<is_3d>,<hor_accuracy>,<ver_accuracy>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GPSFIX

**Mô tả:** Cưỡng bức yêu cầu cập nhật ngay 1 tọa độ GPS mới. Kết quả đẩy qua URC.

**Cú pháp đọc:**
```
AT+GPSFIX?
```

**Phản hồi đọc:**
```
+GPSFIX: <bool>
OK
```

**Cú pháp ghi:**
```
AT+GPSFIX
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GPSSPOS

**Mô tả:** Đặt vị trí GPS bằng tay (khi GPS ở chế độ manual).

**Cú pháp:**
```
AT+GPSSPOS=<year>,<month>,<day>,<hour>,<minute>,<second>,<millisecond>,<lat>,<lon>,<heading>,<speed>,[<altitude>],[<hdop>],[<vdop>],[<is3d>],[<hor_accuracy>],[<ver_accuracy>]
```

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GPSFTO

**Mô tả:** Đọc/ghi thời gian timeout tối đa để lấy GPS fix.

**Cú pháp đọc:**
```
AT+GPSFTO?
```

**Phản hồi đọc:**
```
+GPSFTO: <num_seconds>
OK
```

**Cú pháp ghi:**
```
AT+GPSFTO=<num_seconds>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GPSFTIMESTATS

**Mô tả:** Đọc thời gian fix trung bình hoặc lần cuối.

**Cú pháp:**
```
AT+GPSFTIMESTATS=<stat_type>
```
`stat_type`: 0 = AVG, 1 = LAST

**Phản hồi:**
```
+GPSFTIMESTATS: <stat_type>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GPSFAILS

**Mô tả:** Đọc/ghi tổng số lần GPS fix thất bại.

**Cú pháp đọc:**
```
AT+GPSFAILS?
```

**Phản hồi đọc:**
```
+GPSFAILS: <total_fix_failures>
OK
```

**Cú pháp ghi:**
```
AT+GPSFAILS=<total_fix_failures>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GPSACS

**Mô tả:** Cấu hình thời gian settle và độ chính xác của GPS.

**Cú pháp đọc:**
```
AT+GPSACS?
```

**Phản hồi đọc:**
```
+GPSACS: <seconds>,<radial_accuracy_m>
OK
```

**Cú pháp ghi:**
```
AT+GPSACS=<seconds>,<radial_accuracy_m>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GPSSTIME

**Mô tả:** Đọc/ghi thời gian cho phép dùng lại fix cũ (stale time) tính bằng phút.

**Cú pháp đọc:**
```
AT+GPSSTIME?
```

**Phản hồi đọc:**
```
+GPSSTIME: <num_minutes>
OK
```

**Cú pháp ghi:**
```
AT+GPSSTIME=<num_minutes>
```
Khoảng: 0-60 phút

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GPSPS

**Mô tả:** Thiết lập chế độ năng lượng cho GPS (Cold start, Warm start, Hot start, Always on).

**Cú pháp đọc:**
```
AT+GPSPS?
```

**Phản hồi đọc:**
```
+GPSPS: <gps_power_mode_enum>
OK
```

**Cú pháp ghi:**
```
AT+GPSPS=<gps_power_mode_enum>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GPSCLOC

**Mô tả:** Đọc/ghi khoảng cách phát hiện thay đổi vị trí (Change Of Location - COL).

**Cú pháp đọc:**
```
AT+GPSCLOC?
```

**Phản hồi đọc:**
```
+GPSCLOC: <col_distance_m>
OK
```

**Cú pháp ghi:**
```
AT+GPSCLOC=<col_distance_m>
```
Tối thiểu 30 mét, tối đa 65535 mét. Mặc định: 100 mét.

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GPSCPOS

**Mô tả:** Đọc/ghi vị trí trung tâm cho Change Of Location.

**Cú pháp đọc:**
```
AT+GPSCPOS?
```

**Phản hồi đọc:**
```
+GPSCPOS: <latitude>,<longitude>
OK
```

**Cú pháp ghi:**
```
AT+GPSCPOS=<latitude>,<longitude>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GNSF

**Mô tả:** Cấu hình cờ thông báo URC cho các sự kiện GPS.

**Cú pháp đọc:**
```
AT+GNSF?
```

**Phản hồi đọc:**
```
+GNSF: <gpsNotifyFlags>
OK
```

**Cú pháp ghi:**
```
AT+GNSF=<gpsNotifyFlags>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+RTCSTALESET

**Mô tả:** Đặt thời gian stale cho RTC (ngày, giờ, phút).

**Cú pháp đọc:**
```
AT+RTCSTALESET?
```

**Phản hồi đọc:**
```
+RTCSTALESET: <day>,<hour>,<minute>
OK
```

**Cú pháp ghi:**
```
AT+RTCSTALESET=<day>,<hour>,<minute>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+UTCTIME

**Mô tả:** Đọc thời gian UTC hiện tại.

**Cú pháp:**
```
AT+UTCTIME?
```

**Phản hồi:**
```
+UTCTIME: <year>,<month>,<day>,<hour>,<minute>,<second>,<millisecond>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

## 7. GPIO & Ngoại vi

### AT+GPIOLIST

**Mô tả:** Liệt kê danh sách GPIO khả dụng và trạng thái.

**Cú pháp:**
```
AT+GPIOLIST=<gpio_type>
```

**Phản hồi:**
```
+GPIOLIST: <key>,<property>,<pin>,<enabled>,<fixed>,<type>,<set_state>,<read_state>,<active_high>,<isr_received>,<description>
...
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GPIOCFGIN

**Mô tả:** Cấu hình GPIO làm đầu vào (Input).

**Cú pháp:**
```
AT+GPIOCFGIN=<reserved>,<key>,<is_active_high>
```

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GPIOCFGOUT

**Mô tả:** Cấu hình GPIO làm đầu ra (Output).

**Cú pháp:**
```
AT+GPIOCFGOUT=<reserved>,<key>
```

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GETGPIOSTATE

**Mô tả:** Đọc trạng thái tín hiệu của một chân GPIO.

**Cú pháp:**
```
AT+GETGPIOSTATE=<key>
```

**Phản hồi:**
```
+GETGPIOSTATE: <state>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+SETGPIOOUT

**Mô tả:** Điều khiển xuất tín hiệu cho GPIO output (Clear/Set/Toggle).

**Cú pháp:**
```
AT+SETGPIOOUT=<key>,<state>
```
`state`: 0 = Clear, 1 = Set, 2 = Toggle

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+TDPROP

**Mô tả:** Cấu hình phát hiện chống giả mạo (Tamper Detect).

**Cú pháp đọc:**
```
AT+TDPROP?
```

**Phản hồi đọc:**
```
+TDPROP: <enabled>,[<key>,<is_active_high>]
OK
```

**Cú pháp ghi:**
```
AT+TDPROP=<enabled>,[<key>,<is_active_high>]
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+LPDPROP

**Mô tả:** Cấu hình phát hiện nguồn điện đường dây (Line Power Detect).

**Cú pháp đọc:**
```
AT+LPDPROP?
```

**Phản hồi đọc:**
```
+LPDPROP: <enabled>,<key>,<is_active_high>
OK
```

**Cú pháp ghi:**
```
AT+LPDPROP=<enabled>,<key>,<is_active_high>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+ADVDPROP

**Mô tả:** Cấu hình phát hiện bật quảng cáo (Advertising Enable Detect).

**Cú pháp đọc:**
```
AT+ADVDPROP?
```

**Phản hồi đọc:**
```
+ADVDPROP: <enabled>,[<key>,<is_active_high>]
OK
```

**Cú pháp ghi:**
```
AT+ADVDPROP=<enabled>,[<key>,<is_active_high>]
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+UART2PROP

**Mô tả:** Cấu hình UART2.

**Cú pháp đọc:**
```
AT+UART2PROP?
```

**Phản hồi đọc:**
```
+UART2PROP: <uart_mode>,[<tx_gpio_key>,<rx_gpio_key>,<baud_rate_enum>]
OK
```

**Cú pháp ghi:**
```
AT+UART2PROP=<uart_mode>,[<tx_gpio_key>,<rx_gpio_key>,<baud_rate_enum>]
```
`uart_mode`: 0 = disabled, 1 = enabled, 2 = enabled with RX wake

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+UART2RXWAKETO

**Mô tả:** Đặt thời gian timeout cho chế độ RX Wake của UART2.

**Cú pháp đọc:**
```
AT+UART2RXWAKETO?
```

**Phản hồi đọc:**
```
+UART2RXWAKETO: <time_s>
OK
```

**Cú pháp ghi:**
```
AT+UART2RXWAKETO=<time_s>
```
Phạm vi: 1 giây đến 15 phút.

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+ADCREAD

**Mô tả:** Đọc giá trị điện áp tín hiệu Analog (AIN0 đến AIN7).

**Cú pháp:**
```
AT+ADCREAD=<analog_input>,<channel>
```

**Phản hồi:**
```
+ADCREAD: <voltage>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GPIONSF

**Mô tả:** Cấu hình cờ thông báo URC cho GPIO.

**Cú pháp đọc:**
```
AT+GPIONSF?
```

**Phản hồi đọc:**
```
+GPIONSF: <gpioNotifyFlags>
OK
```

**Cú pháp ghi:**
```
AT+GPIONSF=<gpioNotifyFlags>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

## 8. Input Mapping và Input Functions

### AT+INCNT

**Mô tả:** Đếm số lượng nguồn input có sẵn.

**Cú pháp:**
```
AT+INCNT=<input_source>
```
`input_source`: 0 = ALL, 1 = GPIO, 2 = BLE, 3 = ACCELEROMETER

**Phản hồi:**
```
+INCNT: <input_source>,<count>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+INLIST

**Mô tả:** Liệt kê các nguồn input có sẵn để mapping.

**Cú pháp:**
```
AT+INLIST=<input_source>
```

**Phản hồi:**
```
+INLIST: <input_source_type>,<input_source_id>,<is_open_closed>,<description>
...
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GETINSTATE / AT+SETINSTATE

**Mô tả:** Đọc hoặc đặt giá trị cho input 1-8.

**Cú pháp đọc:**
```
AT+GETINSTATE=<input_num>
```
`input_num`: 1-8

**Phản hồi đọc:**
```
+GETINSTATE: <input_num>,<value>
OK
```

**Cú pháp ghi:**
```
AT+SETINSTATE=<input_num>,<value>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+INMAP

**Mô tả:** Map nguồn input (input_source_id) vào input số 1-8.

**Cú pháp đọc:**
```
AT+INMAP?
```

**Phản hồi đọc:**
```
+INMAP: <input_source_id>,<input_num>
...
OK
```

**Cú pháp ghi:**
```
AT+INMAP=<input_source_id>,<input_num>
```
`input_num` = 0 để un-map.

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GETICS / AT+SETICS

**Mô tả:** Đọc/ghi cài đặt đếm (Count Settings) cho input.

**Cú pháp đọc:**
```
AT+GETICS=<input_num>
```

**Phản hồi đọc:**
```
+GETICS: <input_num>,<count_mode>,<count_modulo>,<count_rollover>,<accumulated_time_mode>,<accumulated_modulo_minutes>,<accumulated_time_rollover>,<transition_event_mode>,<undesired_state_mode>
OK
```

**Cú pháp ghi:**
```
AT+SETICS=<input_num>,<count_mode>,<count_modulo>,<count_rollover>,<accumulated_time_mode>,<accumulated_modulo_minutes>,<accumulated_time_rollover>,<transition_event_mode>,<undesired_state_mode>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GCMS

**Mô tả:** Đọc/ghi cài đặt Count toàn cục.

**Cú pháp đọc:**
```
AT+GCMS?
```

**Phản hồi đọc:**
```
+GCMS: <count_mode_enabled>,<undesired_state_interval_minutes>,<power_on_delay_minutes>,<transition_hysteresis_minutes>
OK
```

**Cú pháp ghi:**
```
AT+GCMS=<count_mode_enabled>,<undesired_state_interval_minutes>,<power_on_delay_minutes>,<transition_hysteresis_minutes>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+ICSTAT

**Mô tả:** Đọc thống kê thời gian thực cho input.

**Cú pháp:**
```
AT+ICSTAT=<input_num>
```

**Phản hồi:**
```
+ICSTAT: <count_total>,<accum_time_total>,<is_active>,<state_change_missed>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+CSTATE?

**Mô tả:** Đọc trạng thái của Count module.

**Cú pháp:**
```
AT+CSTATE?
```

**Phản hồi:**
```
+CSTATE: <count_module_enabled>,<power_on_delay_minutes>,<num_configured_inputs>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GETCNTDATA

**Mô tả:** Đọc dữ liệu payload user cho Count message.

**Cú pháp:**
```
AT+GETCNTDATA=<input_num>
```

**Phản hồi:**
```
+GETCNTDATA: <payload_length>,<hex_str>
OK
```

---

### AT+CSNF

**Mô tả:** Cấu hình cờ thông báo URC cho Count.

**Cú pháp đọc:**
```
AT+CSNF?
```

**Phản hồi đọc:**
```
+CSNF: <count_notify_flags>
OK
```

**Cú pháp ghi:**
```
AT+CSNF=<count_notify_flags>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

## 9. Gia tốc kế (Accelerometer)

### AT+ACCSTAT

**Mô tả:** Bật/tắt module gia tốc kế.

**Cú pháp đọc:**
```
AT+ACCSTAT?
```

**Phản hồi đọc:**
```
+ACCSTAT: <accelerometer_status_enum>
OK
```

**Cú pháp ghi:**
```
AT+ACCSTAT=<accelerometer_status_enum>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+ACCMMT

**Mô tả:** Điều chỉnh độ nhạy phát hiện chuyển động, rung động, lật xoay.

**Cú pháp đọc:**
```
AT+ACCMMT?
```

**Phản hồi đọc:**
```
+ACCMMT: <scale>,<sensitivity>,<orientation_change_enabled>,<vibration_continuous_time>,<vibration_lacking_time>
OK
```

**Cú pháp ghi:**
```
AT+ACCMMT=<scale>,<sensitivity>,<orientation_change_enabled>,<vibration_continuous_time>,<vibration_lacking_time>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+ACCOMSET

**Mô tả:** Cài đặt điều kiện khớp hướng (Orientation Match).

**Cú pháp đọc:**
```
AT+ACCOMSET?
```

**Phản hồi đọc:**
```
+ACCOMSET: <orientation_match_bitmap>
OK
```

**Cú pháp ghi:**
```
AT+ACCOMSET=<orientation_match_bitmap>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+ACCOMSTATE

**Mô tả:** Đọc trạng thái khớp hướng.

**Cú pháp:**
```
AT+ACCOMSTATE?
```

**Phản hồi:**
```
+ACCOMSTATE: <bool>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+ACCOSTATE

**Mô tả:** Đọc trạng thái hướng hiện tại (orientation bitmap).

**Cú pháp:**
```
AT+ACCOSTATE?
```

**Phản hồi:**
```
+ACCOSTATE: <orientation_bitmap>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+ACCSETMOT

**Mô tả:** Đặt trạng thái chuyển động bằng tay (khi ở chế độ manual).

**Cú pháp đọc:**
```
AT+ACCSETMOT?
```

**Phản hồi đọc:**
```
OK
```

**Cú pháp ghi:**
```
AT+ACCSETMOT=<motion_detected>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+ANSF

**Mô tả:** Cấu hình cờ thông báo URC cho gia tốc kế.

**Cú pháp đọc:**
```
AT+ANSF?
```

**Phản hồi đọc:**
```
+ANSF: <accelerometerNotifyFlags>
OK
```

**Cú pháp ghi:**
```
AT+ANSF=<accelerometerNotifyFlags>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

## 10. Quản lý năng lượng

### AT+PWRSTATE

**Mô tả:** Đọc hoặc cấu hình trạng thái tiêu thụ điện.

**Cú pháp đọc:**
```
AT+PWRSTATE?
```

**Phản hồi đọc:**
```
+PWRSTATE: <power_state>
OK
```

**Cú pháp ghi:**
```
AT+PWRSTATE=<power_state>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

**Các trạng thái:**
- `0` = Normal
- `1` = Partial Suspend
- `2` = Full Suspend
- `3` = Full Off
- `4` = Factory

---

### AT+PWRMANUAL

**Mô tả:** Bật/tắt chế độ điều khiển nguồn bằng tay.

**Cú pháp đọc:**
```
AT+PWRMANUAL?
```

**Phản hồi đọc:**
```
+PWRMANUAL: <manual_mode_enabled>
OK
```

**Cú pháp ghi:**
```
AT+PWRMANUAL=<manual_mode_enabled>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+PWRMEAS

**Mô tả:** Chọn kiểu đo nguồn (Voltage hoặc State of Charge).

**Cú pháp đọc:**
```
AT+PWRMEAS?
```

**Phản hồi đọc:**
```
+PWRMEAS: <power_meas_type_enum>
OK
```

**Cú pháp ghi:**
```
AT+PWRMEAS=<power_meas_type_enum>
```
0 = Voltage, 1 = SOC

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+PSUSPVOLT

**Mô tả:** Đọc/ghi ngưỡng điện áp cho Partial Suspend.

**Cú pháp đọc:**
```
AT+PSUSPVOLT?
```

**Phản hồi đọc:**
```
+PSUSPVOLT: <voltage>
OK
```

**Cú pháp ghi:**
```
AT+PSUSPVOLT=<voltage>
```
Khoảng: 2.6V - 4.0V

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+FSUPSVOLT

**Mô tả:** Đọc/ghi ngưỡng điện áp cho Full Suspend.

**Cú pháp đọc:**
```
AT+FSUPSVOLT?
```

**Phản hồi đọc:**
```
+FSUPSVOLT: <voltage>
OK
```

**Cú pháp ghi:**
```
AT+FSUPSVOLT=<voltage>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+FOFFVOLT

**Mô tả:** Đọc/ghi ngưỡng điện áp cho Full Off.

**Cú pháp đọc:**
```
AT+FOFFVOLT?
```

**Phản hồi đọc:**
```
+FOFFVOLT: <voltage>
OK
```

**Cú pháp ghi:**
```
AT+FOFFVOLT=<voltage>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+FULLOFF

**Mô tả:** Ép thiết bị tắt nguồn hoàn toàn (Full Off).

**Cú pháp đọc:**
```
AT+FULLOFF?
```

**Phản hồi đọc:**
```
+FULLOFF: <off_pending>,<remaining_minutes>
OK
```

**Cú pháp ghi:**
```
AT+FULLOFF=0
```
(Tham số bắt buộc là 0)

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+BATTVNOTIFY

**Mô tả:** Đọc/ghi ngưỡng thông báo điện áp pin thấp.

**Cú pháp đọc:**
```
AT+BATTVNOTIFY?
```

**Phản hồi đọc:**
```
+BATTVNOTIFY: <voltage>
OK
```

**Cú pháp ghi:**
```
AT+BATTVNOTIFY=<voltage>
```
Đặt 0 để tắt.

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+BATTVOLT

**Mô tả:** Đọc điện áp pin hiện tại.

**Cú pháp:**
```
AT+BATTVOLT?
```

**Phản hồi:**
```
+BATTVOLT: <voltage>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+PSUSPOSC

**Mô tả:** Đọc/ghi ngưỡng SOC cho Partial Suspend.

**Cú pháp đọc:**
```
AT+PSUSPOSC?
```

**Phản hồi đọc:**
```
+PSUSPOSC: <charge_percent>
OK
```

**Cú pháp ghi:**
```
AT+PSUSPOSC=<charge_percent>
```
0-100

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+FSUPSSOC

**Mô tả:** Đọc/ghi ngưỡng SOC cho Full Suspend.

**Cú pháp đọc:**
```
AT+FSUPSSOC?
```

**Phản hồi đọc:**
```
+FSUPSSOC: <charge_percent>
OK
```

**Cú pháp ghi:**
```
AT+FSUPSSOC=<charge_percent>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+OFFSOC

**Mô tả:** Đọc/ghi ngưỡng SOC cho Full Off.

**Cú pháp đọc:**
```
AT+OFFSOC?
```

**Phản hồi đọc:**
```
+OFFSOC: <charge_percent>
OK
```

**Cú pháp ghi:**
```
AT+OFFSOC=<charge_percent>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+BATTSNOTIFY

**Mô tả:** Đọc/ghi ngưỡng thông báo SOC pin thấp.

**Cú pháp đọc:**
```
AT+BATTSNOTIFY?
```

**Phản hồi đọc:**
```
+BATTSNOTIFY: <soc_percent>
OK
```

**Cú pháp ghi:**
```
AT+BATTSNOTIFY=<soc_percent>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+BATTSOC

**Mô tả:** Đọc SOC pin hiện tại.

**Cú pháp:**
```
AT+BATTSOC?
```

**Phản hồi:**
```
+BATTSOC: <soc_percent>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+BATTTEMP

**Mô tả:** Đọc nhiệt độ pin (độ C).

**Cú pháp:**
```
AT+BATTTEMP?
```

**Phản hồi:**
```
+BATTTEMP: <temp>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+MCUTEMP

**Mô tả:** Đọc nhiệt độ MCU (độ C).

**Cú pháp:**
```
AT+MCUTEMP?
```

**Phản hồi:**
```
+MCUTEMP: <temp>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+TXTEMP

**Mô tả:** Đọc nhiệt độ bộ phát (độ C).

**Cú pháp:**
```
AT+TXTEMP?
```

**Phản hồi:**
```
+TXTEMP: <temp>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+TXTEMPTHRESH

**Mô tả:** Đọc/ghi ngưỡng nhiệt độ quá nhiệt của bộ phát.

**Cú pháp đọc:**
```
AT+TXTEMPTHRESH?
```

**Phản hồi đọc:**
```
+TXTEMPTHRESH: <temperature>
OK
```

**Cú pháp ghi:**
```
AT+TXTEMPTHRESH=<temperature>
```
0.0 - 255.0

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+TXTEMPLOWTHRESH

**Mô tả:** Đọc/ghi ngưỡng nhiệt độ dưới nhiệt độ của bộ phát.

**Cú pháp đọc:**
```
AT+TXTEMPLOWTHLD?
```

**Phản hồi đọc:**
```
+TXTEMPLOWTHLD: <temperature>
OK
```

**Cú pháp ghi:**
```
AT+TXTEMPLOWTHLD=<temperature>
```
-255 đến < overtemp_threshold

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+GETTNS / AT+SETTNS

**Mô tả:** Đọc/ghi cài đặt thông báo nhiệt độ.

**Cú pháp đọc:**
```
AT+GETTNS=<temp_type>
```
`temp_type`: 0 = MCU, 1 = Batt, 2 = TX

**Phản hồi đọc:**
```
+GETTNS: <temp_type>,<high_temp>,<low_temp>
OK
```

**Cú pháp ghi:**
```
AT+SETTNS=<temp_type>,<high_temp>,<low_temp>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+MCUREBOOT

**Mô tả:** Khởi động lại MCU.

**Cú pháp:**
```
AT+MCUREBOOT
```

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+TXREBOOT

**Mô tả:** Khởi động lại ASIC bộ phát.

**Cú pháp:**
```
AT+TXREBOOT=<is_cold_reset>
```
`is_cold_reset`: 0 (warm), 1 (cold)

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+RESETFLAG / AT+RESETCLEAR

**Mô tả:** Đọc và xóa cờ nguyên nhân khởi động lại MCU.

**Cú pháp đọc:**
```
AT+RESETFLAG?
```

**Phản hồi đọc:**
```
OK
```

**Cú pháp xóa:**
```
AT+RESETCLEAR
```

**Phản hồi:**
```
OK
```

---

### AT+PNSF

**Mô tả:** Cấu hình cờ thông báo URC cho năng lượng.

**Cú pháp đọc:**
```
AT+PNSF?
```

**Phản hồi đọc:**
```
+PNSF: <powerNotifyFlags>
OK
```

**Cú pháp ghi:**
```
AT+PNSF=<powerNotifyFlags>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

## 11. Ghi nhật ký (Data Logging)

### AT+LOGLOCEN

**Mô tả:** Bật/tắt lưu tọa độ GPS vào flash.

**Cú pháp đọc:**
```
AT+LOGLOCEN?
```

**Phản hồi đọc:**
```
+LOGLOCEN: <enable>
OK
```

**Cú pháp ghi:**
```
AT+LOGLOCEN=<enable>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+LOCLOGS

**Mô tả:** Trích xuất lịch sử vị trí GPS theo khoảng thời gian.

**Cú pháp:**
```
AT+LOCLOGS=<lower_timestamp>,<higher_timestamp>
```

**Phản hồi:**
```
OK
+URC: "LocLogs",<number_of_logs>,<timestamp>,<year>,<month>,<day>,<hour>,<minute>,<second>,<millisecond>,<lat>,<lon>,<heading>,<speed>,<altitude>,<hdop>,<vdop>,<is3D>,<horAccuracy>,<verAccuracy>
...
```
Hoặc:
```
OK
"ERROR: 1 NO LOGS IN THE TIME RANGE"
```

---

### AT+MSGLOGS

**Mô tả:** Trích xuất nhật ký metadata OTA.

**Cú pháp:**
```
AT+MSGLOGS=<lower_timestamp>,<higher_timestamp>
```

**Phản hồi:**
```
OK
+URC: "MsgMetadata",<number_of_logs>,<timestamp>,<umn>,<msg_type>,<sub_type>,<mod_msg_type>,<num_attempts>,<error_exception>
...
```
Hoặc:
```
OK
"ERROR: 1 NO LOGS IN THE TIME RANGE"
```

---

### AT+DBGLOGS

**Mô tả:** Đọc nhật ký debug.

**Cú pháp:**
```
AT+DBGLOGS=<lower_timestamp>,<higher_timestamp>
```

**Phản hồi:**
```
OK
+URC: <number_of_logs>,<timestamp>,<log_string>
...
```
Hoặc:
```
OK
"ERROR: 1 NO LOGS IN THE TIME RANGE"
```

---

### AT+FLMLOGS

**Mô tả:** Đọc nhật ký Forward Link messages (RM200).

**Cú pháp:**
```
AT+FLMLOGS=<lower_timestamp>,<higher_timestamp>
```

**Phản hồi:**
```
OK
+URC: "Modem FL Status",<number_of_logs>,<timestamp>,<ModemEventTypes>,<modem_msg_ack_enum>,<ack_umn>,<ack_packets>,<ack_bitmask>
...
```
Hoặc:
```
OK
"ERROR: 1 NO LOGS IN THE TIME RANGE"
```

---

### AT+LOGGETBACKENDST

**Mô tả:** Đọc trạng thái backend log.

**Cú pháp:**
```
AT+LOGGETBACKENDST=<backend>
```

**Phản hồi:**
```
+LOGGETBACKENDST: <backend>,<is_enabled>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+LOGSETBACKENDST

**Mô tả:** Đặt trạng thái backend log (bật/tắt).

**Cú pháp:**
```
AT+LOGSETBACKENDST=<backend>,<enable>
```

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+LOGGETMODMODE

**Mô tả:** Đọc chế độ log cho một module cụ thể.

**Cú pháp:**
```
AT+LOGGETMODMODE=<backend>,<module_id>
```

**Phản hồi:**
```
+LOGGETMODMODE: <backend>,<module_id>,<mode>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+LOGSETMODMODE

**Mô tả:** Đặt chế độ log cho một module cụ thể.

**Cú pháp:**
```
AT+LOGSETMODMODE=<backend>,<module_id>,<mode>
```

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+LOGSETGROUPMODE

**Mô tả:** Đặt chế độ log cho một nhóm module.

**Cú pháp:**
```
AT+LOGSETGROUPMODE=<backend>,<group_id>,<mode>
```

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+LOGSETGLOBALMODE

**Mô tả:** Đặt chế độ log toàn cục.

**Cú pháp:**
```
AT+LOGSETGLOBALMODE=<backend>,<mode>
```

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+LNSF

**Mô tả:** Cấu hình cờ thông báo URC cho logging.

**Cú pháp đọc:**
```
AT+LNSF?
```

**Phản hồi đọc:**
```
+LNSF: <loggingNotifyFlags>
OK
```

**Cú pháp ghi:**
```
AT+LNSF=<loggingNotifyFlags>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

## 12. Chẩn đoán (Diagnostics)

### AT+HEALTHCKSET

**Mô tả:** Đặt tần suất gửi Health Check (số lần mỗi tháng).

**Cú pháp đọc:**
```
AT+HEALTHCKSET?
```

**Phản hồi đọc:**
```
+HEALTHCKSET: <transmissions_per_month>
OK
```

**Cú pháp ghi:**
```
AT+HEALTHCKSET=<transmissions_per_month>
```
1-30 lần/tháng.

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+HEALTHCBURSTS

**Mô tả:** Đặt số burst cho mỗi lần gửi Health Check.

**Cú pháp đọc:**
```
AT+HEALTHCBURSTS?
```

**Phản hồi đọc:**
```
+HEALTHCBURSTS: <num_bursts>
OK
```

**Cú pháp ghi:**
```
AT+HEALTHCBURSTS=<num_bursts>
```
3-5 bursts.

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+DHSTATUS?

**Mô tả:** Đọc toàn bộ tham số chẩn đoán Health Check.

**Cú pháp:**
```
AT+DHSTATUS?
```

**Phản hồi:**
```
+DHSTATUS: <battery_low>,<gps_fault>,<transmitter_fault>,<line_power>,<fw_major>,<fw_minor>,<fw_patch>,<gps_fail_count>,<transmission_count>,<avg_fix_time>,<ble_conn_count>,<board_reset>,<tx_temp_over>,<tx_ras>,<tx_pwr>,<tx_preempt>,<tx_user_abort>,<config_major>,<config_minor>,<tx_queue_add_cnt>,<tx_failures_cnt>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

## 13. Cấu hình BLE

### AT+BLEPREF

**Mô tả:** Đổi chuỗi tiền tố (prefix) tên thiết bị khi phát sóng Bluetooth.

**Cú pháp đọc:**
```
AT+BLEPREF?
```

**Phản hồi đọc:**
```
+BLEPREF: <prefix_str>
OK
```

**Cú pháp ghi:**
```
AT+BLEPREF=<prefix_str>
```
Độ dài 1-3 ký tự.

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+BLEPWR

**Mô tả:** Chỉnh công suất phát BLE.

**Cú pháp đọc:**
```
AT+BLEPWR?
```

**Phản hồi đọc:**
```
+BLEPWR: <power_level>
OK
```

**Cú pháp ghi:**
```
AT+BLEPWR=<power_level>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+BLEADVINT

**Mô tả:** Đọc/ghi khoảng thời gian quảng cáo BLE (ms).

**Cú pháp đọc:**
```
AT+BLEADVINT?
```

**Phản hồi đọc:**
```
+BLEADVINT: <interval_ms>
OK
```

**Cú pháp ghi:**
```
AT+BLEADVINT=<interval_ms>
```
Khoảng: 100 - 10240 ms. Mặc định: 500 ms.

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+CFGEN

**Mô tả:** Bật/tắt dịch vụ cấu hình BLE Config Service.

**Cú pháp đọc:**
```
AT+CFGEN?
```

**Phản hồi đọc:**
```
+CFGEN: <enable>
OK
```

**Cú pháp ghi:**
```
AT+CFGEN=<enable>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+NUSEN

**Mô tả:** Bật/tắt Nordic UART Service (NUS).

**Cú pháp đọc:**
```
AT+NUSEN?
```

**Phản hồi đọc:**
```
+NUSEN: <enable>
OK
```

**Cú pháp ghi:**
```
AT+NUSEN=<enable>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+ENTERDFU

**Mô tả:** Buộc thiết bị vào chế độ Bootloader để chờ nạp firmware mới (DFU).

**Cú pháp:**
```
AT+ENTERDFU
```

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

## 14. Cảm biến BLE Smart One (S1)

### AT+S1SENSVCEN

**Mô tả:** Bật/tắt dịch vụ cảm biến Smart One.

**Cú pháp đọc:**
```
AT+S1SENSVCEN?
```

**Phản hồi đọc:**
```
+S1SENSVCEN: <enabled>
OK
```

**Cú pháp ghi:**
```
AT+S1SENSVCEN=<enabled>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+S1SENSVCSCANINT

**Mô tả:** Đọc/ghi khoảng thời gian quét cho S1 Sensor Service (giây).

**Cú pháp đọc:**
```
AT+S1SENSVCSCANINT?
```

**Phản hồi đọc:**
```
+S1SENSVCSCANINT: <scan_interval>
OK
```

**Cú pháp ghi:**
```
AT+S1SENSVCSCANINT=<scan_interval>
```
Khoảng: 3-240 giây.

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+S1SENSVCSECKEY

**Mô tả:** Đọc/ghi public key cho S1 Sensor Service.

**Cú pháp đọc:**
```
AT+S1SENSVCSECKEY?
```

**Phản hồi đọc:**
```
+S1SENSVCSECKEY: <hex_str>
OK
```

**Cú pháp ghi:**
```
AT+S1SENSVCSECKEY=<hex_str>
```
Chuỗi hex 128 ký tự.

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+S1SENSVCESNVERIFY

**Mô tả:** Bật/tắt xác minh ESN cho S1 Sensor Service.

**Cú pháp đọc:**
```
AT+S1SENSVCESNVERIFY?
```

**Phản hồi đọc:**
```
+S1SENSVCESNVERIFY: <enabled>
OK
```

**Cú pháp ghi:**
```
AT+S1SENSVCESNVERIFY=<enabled>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+S1SENSVCUIDVERIFY

**Mô tả:** Bật/tắt xác minh UID cho S1 Sensor Service.

**Cú pháp đọc:**
```
AT+S1SENSVCUIDVERIFY?
```

**Phản hồi đọc:**
```
+S1SENSVCUIDVERIFY: <enabled>
OK
```

**Cú pháp ghi:**
```
AT+S1SENSVCUIDVERIFY=<enabled>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+S1SENSVCSENSTRID

**Mô tả:** Đọc/ghi String ID cho S1 Sensor Service.

**Cú pháp đọc:**
```
AT+S1SENSVCSENSTRID?
```

**Phản hồi đọc:**
```
+S1SENSVCSENSTRID: <string>
OK
```

**Cú pháp ghi:**
```
AT+S1SENSVCSENSTRID=<string>
```
Độ dài 3-10 ký tự.

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

## 15. Ứng dụng Lập lịch (Time of Day / Interval)

### AT+TODML

**Mô tả:** Đọc danh sách tin nhắn lập lịch theo giờ trong ngày (TOD).

**Cú pháp:**
```
AT+TODML?
```

**Phản hồi:**
```
+TODML: <Number_of_entries>
<index>,<type>,<subtype>,<mod_msg_type>,<hour>,<minute>,<second>
...
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+ATODM

**Mô tả:** Thêm một lịch gửi tin nhắn Time of Day mới.

**Cú pháp:**
```
AT+ATODM=<type>,<subtype>,<ModMessageType>,<hour>,<minute>,<second>
```

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+DTODM

**Mô tả:** Xóa một lịch gửi TOD theo index.

**Cú pháp:**
```
AT+DTODM=<index>
```

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+IML

**Mô tả:** Đọc danh sách tin nhắn lập lịch theo chu kỳ (Interval).

**Cú pháp:**
```
AT+IML?
```

**Phản hồi:**
```
+IML: <number_of_entries>
<index>,<type>,<subtype>,<mod_msg_type>,<day>,<hour>,<minute>,<second>
...
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+AIM

**Mô tả:** Thêm một lịch gửi tin nhắn Interval mới.

**Cú pháp:**
```
AT+AIM=<type>,<subtype>,<ModMessageType>,<day>,<hour>,<minute>,<second>
```

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+DIM

**Mô tả:** Xóa một lịch gửi Interval theo index.

**Cú pháp:**
```
AT+DIM=<index>
```

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+DLISTALL

**Mô tả:** Xóa toàn bộ danh sách tin nhắn hẹn giờ/chu kỳ.

**Cú pháp:**
```
AT+DLISTALL
```

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

## 16. Tin nhắn sự kiện hệ thống (System Event)

### AT+GETEVOTA / AT+SETEVOTA

**Mô tả:** Đọc/ghi cấu hình tin nhắn sự kiện cho Input.

**Cú pháp đọc:**
```
AT+GETEVOTA=<input_num>
```

**Phản hồi đọc:**
```
+GETEVOTA: <event_input_enabled>,<ota_message_type>,<undesired_state_interval_minutes>,<desired_state_interval_minutes>,<low_batt_update_rate_minutes>,<ota_transition_hysteresis_minutes>,<previous_track_message_enabled>
OK
```

**Cú pháp ghi:**
```
AT+SETEVOTA=<input_num>,<event_input_enabled>,<ota_message_type>,<undesired_state_interval_minutes>,<desired_state_interval_minutes>,<low_batt_update_rate_minutes>,<ota_transition_hysteresis_minutes>,<previous_track_message_enabled>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+SYSEVTDEVRST

**Mô tả:** Đọc/cấu hình loại tin nhắn OTA tự động gửi khi thiết bị reset.

**Cú pháp đọc:**
```
AT+SYSEVTDEVRST?
```

**Phản hồi đọc:**
```
+SYSEVTDEVRST: <dev_reset_ota_type_enum>
OK
```

**Cú pháp ghi:**
```
AT+SYSEVTDEVRST=<dev_reset_ota_type_enum>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+CANSF

**Mô tả:** Đọc/Ghi cờ thông báo URC cho Count/OTA events.

**Cú pháp đọc:**
```
AT+CANSF?
```

**Phản hồi đọc:**
```
+CANSF: <countNotifyFlags>
OK
```

**Cú pháp ghi:**
```
AT+CANSF=<otaeventNotifyFlags>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

## 17. Ứng dụng Theo dõi (Track)

### AT+TRACK

**Mô tả:** Bắt đầu phiên theo dõi mới hoặc đọc cấu hình hiện tại.

**Cú pháp đọc:**
```
AT+TRACK?
```

**Phản hồi đọc:**
```
+TRACK: <mode>,<msg_type>,<COL_num_tx>,<at_rest_rate_minutes>,<low_bat_rate_minutes>,<in_motion_rate_minutes>,<prev_track_enabled>,<col_message_wanted>,<recenter_message_wanted>,<in_vibration_check_rate>
OK
```

**Cú pháp ghi:**
```
AT+TRACK=<mode>,<msg_type>,<COL_num_tx>,<at_rest_rate_minutes>,<low_bat_rate_minutes>,<in_motion_rate_minutes>,<prev_track_enabled>,<col_message_wanted>,<recenter_message_wanted>,[<in_vibration_check_rate>]
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+CTRACK

**Mô tả:** Hủy và dừng ngay lập tức phiên theo dõi đang diễn ra.

**Cú pháp:**
```
AT+CTRACK
```

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+TNSF

**Mô tả:** Cấu hình cờ thông báo Track (URC) lưu trong NV memory.

**Cú pháp đọc:**
```
AT+TNSF?
```

**Phản hồi đọc:**
```
+TNSF: <bitmask_value>
OK
```

**Cú pháp ghi:**
```
AT+TNSF=<bitmask_value>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+TANSF

**Mô tả:** Cấu hình cờ thông báo Track (URC) không lưu trữ (volatile).

**Cú pháp đọc:**
```
AT+TANSF?
```

**Phản hồi đọc:**
```
+TANSF: <bitmask_value>
OK
```

**Cú pháp ghi:**
```
AT+TANSF=<bitmask_value>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

## 18. Cảm biến BLE (BLE Sensors)

### AT+BLESENLOCK

**Mô tả:** Khóa/mở khóa cài đặt cảm biến.

**Cú pháp đọc:**
```
AT+BLESENLOCK?
```

**Phản hồi đọc:**
```
+BLESENLOCK: <state>
OK
```

**Cú pháp ghi:**
```
AT+BLESENLOCK=<state>
```
`state`: 1 = lock, 0 = unlock

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+BLESENRECURVAL

**Mô tả:** Đọc/ghi số lần đọc liên tiếp để kích hoạt delta trigger.

**Cú pháp đọc:**
```
AT+BLESENRECURVAL?
```

**Phản hồi đọc:**
```
+BLESENRECURVAL: <count>
OK
```

**Cú pháp ghi:**
```
AT+BLESENRECURVAL=<count>
```
Mặc định: 3

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+BLESENIDEALOTAREQ

**Mô tả:** Bật/tắt OTA message khi cảm biến trở về trạng thái lý tưởng.

**Cú pháp đọc:**
```
AT+BLESENIDEALOTAREQ?
```

**Phản hồi đọc:**
```
+BLESENIDEALOTAREQ: <enable>
OK
```

**Cú pháp ghi:**
```
AT+BLESENIDEALOTAREQ=<enable>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+BLESENLOSTCOUNT

**Mô tả:** Đọc/ghi số chu kỳ quét liên tiếp để đánh dấu cảm biến bị mất.

**Cú pháp đọc:**
```
AT+BLESENLOSTCOUNT?
```

**Phản hồi đọc:**
```
+BLESENLOSTCOUNT: <count>
OK
```

**Cú pháp ghi:**
```
AT+BLESENLOSTCOUNT=<count>
```
Mặc định: 10

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+BLESENLOSTSTATUS

**Mô tả:** Kiểm tra trạng thái mất kết nối của cảm biến BLE.

**Cú pháp:**
```
AT+BLESENLOSTSTATUS?
```

**Phản hồi:**
```
+BLESENLOSTSTATUS: <identity_key>,<lost_status>
...
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+BLESENSCANTIME

**Mô tả:** Đọc/ghi thời gian quét tối đa cho mỗi cảm biến (giây).

**Cú pháp đọc:**
```
AT+BLESENSCANTIME?
```

**Phản hồi đọc:**
```
+BLESENSCANTIME: <scan_time_s>
OK
```

**Cú pháp ghi:**
```
AT+BLESENSCANTIME=<scan_time_s>
```
1-30 giây. Mặc định: 2 giây.

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+BLESENCFG

**Mô tả:** Thêm cấu hình cảm biến (sensor configuration).

**Cú pháp:**
```
AT+BLESENCFG=<type>,<identity_key>,<mod_msg_type>,<ideal_value>,<delta_value>,<missed_state_count_trigger_value>,<low_battery_mv>,<customer_id_number>,<sensor_2_ideal_value>,<sensor_2_delta_value>,<sensor_2_delta_type>,[undesired_state_msg_interval_minutes]
```

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+BLESENDETAILS

**Mô tả:** Thêm chi tiết cảm biến (tên, địa chỉ MAC).

**Cú pháp:**
```
AT+BLESENDETAILS=<identity_key>,<name>,[<mac_address>]
```

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+BLESENGET

**Mô tả:** Truy vấn danh sách cảm biến đã thêm.

**Cú pháp:**
```
AT+BLESENGET?
```

**Phản hồi:**
```
+BLESENGET: <name>,<type>,<identity_key>,<mod_msg_type>,<ideal_value>,<delta_value>,<missed_state_count_trigger_value>,<low_battery_mv>,<customer_id_number>,<sensor_2_ideal_value>,<sensor_2_delta_value>,<sensor_2_delta_type>,<mac_address>,<undesired_state_msg_interval_minutes>
...
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+BLESENREM

**Mô tả:** Xóa một cảm biến theo identity_key.

**Cú pháp:**
```
AT+BLESENREM=<identity_key>
```

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+BLESENLOCATE

**Mô tả:** Kích hoạt chế độ Locate (quét BLE trong 30 giây, lưu MAC cảm biến).

**Cú pháp:**
```
AT+BLESENLOCATE
```

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+BLESENLOCATED

**Mô tả:** Kiểm tra trạng thái đã định vị cảm biến.

**Cú pháp:**
```
AT+BLESENLOCATED?
```

**Phản hồi:**
```
+BLESENLOCATED: <status>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+BLESENACTIVE

**Mô tả:** Bật/tắt chế độ kích hoạt cảm biến (activation mode).

**Cú pháp đọc:**
```
AT+BLESENACTIVE?
```

**Phản hồi đọc:**
```
+BLESENACTIVE: <enable>
OK
```

**Cú pháp ghi:**
```
AT+BLESENACTIVE=<enable>
```

**Phản hồi ghi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

## 19. Cấu hình OTA (Over-The-Air)

### AT+OTACONFIG

**Mô tả:** Đẩy payload cấu hình OTA vào thiết bị.

**Cú pháp:**
```
AT+OTACONFIG=<byte1...byte128>
```
Payload theo định dạng: byte1: Application config identifier (0x7F), byte2: flags, byte3: config ID, byte4: total packets, byte5-6: uncompressed length, tiếp theo compressed data, cuối cùng CRC.

**Phản hồi:**
```
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

---

### AT+OTACONFIGSTATUS?

**Mô tả:** Truy vấn trạng thái gói OTA gần nhất.

**Cú pháp:**
```
AT+OTACONFIGSTATUS?
```

**Phản hồi:**
```
+OTACFGSTATUS: <Response_flag>,<Configuration_ID>
OK
```
Hoặc:
```
+ERROR: <mã_lỗi>
```

**Cờ trạng thái:**
- `0x01`: Internal Error
- `0x02`: Packet Error (thường không dùng)
- `0x04`: CRC Mismatch
- `0x08`: Decompression Error
- `0x10`: Write Permission Error
- `0x20`: AT Command Execution Error
- `0x80`: Success

---

## Phụ lục: Mã lỗi bổ sung

### Mã lỗi hàng đợi gửi tin (Message Queue TX Errors)

| Mã lỗi | Tên | Mô tả |
|--------|-----|-------|
| 0 | MESSAGE_QUEUE_TX_ERROR_NONE | Không có lỗi |
| 1 | MESSAGE_QUEUE_TX_ERROR_OVER_TEMP | Nhiệt độ quá cao |
| 2 | MESSAGE_QUEUE_TX_ERROR_RAS_EXP | Vào vùng cấm phát sóng RAS |
| 3 | MESSAGE_QUEUE_TX_ERROR_PWR_EXP | Năng lượng/điện áp không đảm bảo |
| 4 | MESSAGE_QUEUE_TX_ERROR_USER_ABORTED | Người dùng hủy |
| 5 | MESSAGE_QUEUE_TX_ERROR_PREEMPTED | Bị chiếm quyền bởi tin nhắn ưu tiên cao hơn |
| 6 | MESSAGE_QUEUE_TX_ERROR_UNDER_TEMP | Nhiệt độ quá thấp |

### Mã lỗi khởi tạo phần cứng (Device Initialization Faults)

| Cờ lỗi | Mô tả |
|--------|-------|
| dev_clock_fault / dev_rtc_fault / dev_hfclk_fault | Lỗi xung nhịp / RTC / HFCLK |
| dev_gpio_fault / dev_uart2_fault | Lỗi GPIO / UART2 |
| dev_ble_fault | Lỗi khởi tạo BLE stack |
| dev_config_fault / dev_log_fault / dev_security_fault | Lỗi flash, log, bảo mật |

---
