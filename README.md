# Part 1A: Esp32-NOW TRANSMITTER
Mô tả hoạt động:
1. ESP32 khởi động và thiết lập giao tiếp Serial Monitor.
2. Đặt ESP32 ở chế độ WIFI_STA (Station Mode)
3. Khởi tạo ESP-NOW bằng `esp_now_init()`
4. Thêm thiết bị nhận (peer) bằng địa chỉ MAC khai báo trong code
5. Gửi tin nhắn "HELLO" đến peer
# code đầy đủ
```cpp
#include <WiFi.h>
#include <esp_now.h>

uint8_t mac[]= {0x88, 0x57, 0x21, 0xBC, 0x56, 0x58};
char n[]="HELLO";

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  esp_now_init();

  esp_now_peer_info_t x={};
  memcpy(x.peer_addr, mac, 6);
  esp_now_add_peer(&x);
  esp_now_send(mac, (uint8_t*)n, sizeof(n));

}

void loop() {


}
```
# Giải thích chi tiết từng phần
1. Thư viện
```cpp
#include <WiFi.h>
#include <esp_now.h>
```
`#include <WiFi.h>`
Thư viện hỗ trợ các chức năng cho WiFi cho ESP32:
`WiFi.mode(WIFI_STA)`: đặt ESP32 ở chế độ trạm (Station mode)
`WiFi.macAddress()`: lấy địa chỉ MAC của ESP32 peer

`#include <esp_now.h>`
Thư viện hỗ trợ giao tiếp không  của ESP32:
`esp_now_init()`: khởi tạo giao thức ESP-NOW
`esp_now_add_peer(&x)`: thêm thiết bị nhận vào danh sách
`esp_now_send(mac, (uint8_t*)n, sizeof(n))`: cấu trúc thông tin của thiết bị nhận: địa chỉ mac thiết bị nhận, con trỏ đến dữ liệu cần, kích thước gói dữ liệu

2. Các biến toàn cục
```cpp
uint8_t mac[]= {0x88, 0x57, 0x21, 0xBC, 0x56, 0x58};
char n[]="HELLO";
```
`uint8_t mac[]= {0x88, 0x57, 0x21, 0xBC, 0x56, 0x58};`: lưu địa chỉ MAC của thiết bị nhận dữ liệu qua ESP-NOW
`char n[]="HELLO";`: văn bản được gửi đi tới thiết bị nhận

3. Hàm `setup()`  
```python
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
```
`Serial.begin(115200)`  
&emsp;Khởi tạo giao tiếp UART (Serial) giữa ESP32 và máy tính.  
&emsp;Tốc độ truyền dữ liệu là 115200 bit/giây, phù hợp cho debug.  
&emsp;Mọi lệnh `Serial.print()` sau này sẽ hiển thị trên Serial Monitor của Arduino IDE.  
`WiFi.mode(WIFI_STA)`   
&emsp;Đặt ESP32 ở chế độ trạm (Station mode).  
&emsp;Ở chế độ này, ESP32 hoạt động như một thiết bị WiFi thông thường, kết nối vào router thay vì phát WiFi.  

```python
esp_now_init();
```
`esp_now_init():`
&emsp;Hàm thực hiện việc khởi động giao thức ESP-NOW trên ESP32, cho phép thiết bị sẵn sàng gửi/nhận gói tin.

```python
esp_now_peer_info_t x={};
  memcpy(x.peer_addr, mac, 6);
  esp_now_add_peer(&x);
  esp_now_send(mac, (uint8_t*)n, sizeof(n));
```
`esp_now_peer_info_t x={}` 
&emsp;Khai báo một cấu trúc dữ liệu để lưu thông tin của peer
`memcpy(x.peer_addr, mac, 6)`
&emsp;Sao chép 6 byte địa chỉ mac của peer vào trường địa chỉ của cấu trúc x
`esp_now_add_peer(&x)`
&emsp;Thêm thiết bị nhận vào danh sách mà ESP32 có thể gửi dữ liệu
`esp_now_send(mac, (uint8_t*)n, sizeof(n));`
&emsp;Thực hiện gửi dữ liệu "HELLO" tới địa chỉ mac

```python
void loop() {
}
```

Kết quả thực thi  
Sau khi nạp code, ESP32 sẽ gửi đi dữ liệu `HELLO` tới thiết bị nhận(peer)


# Part 1B: Esp32-NOW RECEIVER
Mô tả hoạt động:
1. ESP32 khởi động và thiết lập giao tiếp Serial Monitor.
2. Đặt ESP32 ở chế độ WIFI_STA (Station Mode)
3. Khởi tạo ESP-NOW bằng `esp_now_init()`
4. Tạo một hàm callback để xử lí dữ liệu khi nhận dữ liệu bằng `esp_now_register_recv_cb`
5. Khi dữ liệu được gửi đến, nhận và in ra 
# code đầy đủ
```cpp
#include <WiFi.h>
#include <esp_now.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  esp_now_init();
  esp_now_register_recv_cb([](
    const esp_now_recv_info_t *info, const uint8_t *incoming, int len) {
      for(int i=0; i<len; i++) Serial.print((char)incoming[i]);
    }
  );
}

void loop() {
  // put your main code here, to run repeatedly:

}
```
# Giải thích chi tiết từng phần:
1. Thư viện
```cpp
#include <WiFi.h>
#include <esp_now.h>
```
`#include <WiFi.h>`
Thư viện hỗ trợ các chức năng cho WiFi cho ESP32:
`WiFi.mode(WIFI_STA)`: đặt ESP32 ở chế độ trạm (Station mode)

`#include <esp_now.h>`
Thư viện hỗ trợ giao tiếp không  của ESP32:
`esp_now_init()`: khởi tạo giao thức ESP-NOW
`esp_now_register_recv_cb()`: gọi hàm callback khi dữ liệu được gửi 
`esp_now_send(mac, (uint8_t*)n, sizeof(n))`: cấu trúc thông tin của thiết bị gửi

2. Hàm `setup()`
```python
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
```
`Serial.begin(115200)`  
&emsp;Khởi tạo giao tiếp UART (Serial) giữa ESP32 và máy tính.  
&emsp;Tốc độ truyền dữ liệu là 115200 bit/giây, phù hợp cho debug.  
&emsp;Mọi lệnh `Serial.print()` sau này sẽ hiển thị trên Serial Monitor của Arduino IDE.  
`WiFi.mode(WIFI_STA)`   
&emsp;Đặt ESP32 ở chế độ trạm (Station mode).  
&emsp;Ở chế độ này, ESP32 hoạt động như một thiết bị WiFi thông thường, kết nối vào router thay vì phát WiFi.  

```python
esp_now_init();
```
`esp_now_init():`
&emsp;Hàm thực hiện việc khởi động giao thức ESP-NOW trên ESP32, cho phép thiết bị sẵn sàng gửi/nhận gói tin.

```python
esp_now_register_recv_cb([](
    const esp_now_recv_info_t *info, const uint8_t *incoming, int len) {
      for(int i=0; i<len; i++) Serial.print((char)incoming[i]);
    }
  );
}
```
`const esp_now_recv_info_t *info, const uint8_t *incoming, int len)`
&emsp;Đăng ký một hàm ẩn danh (lambda) sẽ được tự động gọi ngay khi ESP32 nhận được dữ liệu từ thiết bị gửi
&emsp;`const esp_now_recv_info_t *info` con trỏ tới cấu trúc chứa metadata của dữ liệu gồm địa chỉ mac thiết bị gửi và cường độ tín 
&emsp;`const uint8_t *incoming` con trỏ tới vị trí đầu tiên của mảng dữ liệu thực tế (payload) mà gói tin ESP-NOW mang theo. Dữ liệu này được lưu dưới dạng byte (uint8_t).
&emsp;`int len` cho ra số byte của dữ liệu
`for(int i=0; i<len; i++) Serial.print((char)incoming[i]);`
&emsp;`for(int i=0; i<len; i++)` vòng lặp chạy từ đầu mảng dữ liệu (i=0) cho đến hết chiều dài của dữ liệu (len).
&emsp;`Serial.print((char)incoming[i])` lấy từng byte (incoming[i]) từ dữ liệu nhận được và thực hiện ép kiểu ((char)) để chuyển đổi giá trị byte đó thành ký tự chữ/số tương ứng

```python
void loop() {
}
```

Kết quả thực thi  
Sau khi nạp code, Serial Monitor sẽ hiển thị:
1. Hiển thị thông báo `ESP32 Receiver đã sẵn sàng nhận dữ liệu... `
2. Sau khi nhận được dữ liệu từ thiết bị gửi, in ra `HELLO`
