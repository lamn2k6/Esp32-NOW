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
