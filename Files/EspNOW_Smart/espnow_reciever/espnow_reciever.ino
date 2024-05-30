#include <esp_now.h>
#include <WiFi.h>
#define CHANNEL 1

uint8_t newData;
int count;
float RSSI_1m= -38.0;
float N = 2.4;
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("RX_1", "RX_1_Password", CHANNEL, 0);

  esp_now_init();
  esp_now_register_recv_cb(OnDataRecv);
}
void loop() {
  float RSSI = newData;
  RSSI -= 255;
  float Distance = pow(10, (((RSSI_1m - RSSI)) / (10 * N)));
  Serial.println(Distance);
  delay(7000);
}
/** callback when data is recv from Master **/
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
  //Serial.print("I just received -> ");
  //Serial.print(*data);
  memcpy(&newData, data, sizeof(newData));
}