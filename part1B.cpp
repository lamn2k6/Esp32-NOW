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
