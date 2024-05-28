#include <esp_now.h>
#include <WiFi.h>

#define CHANNEL 1

uint8_t newData;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  Serial.println("wifi init");
  pinMode(2, OUTPUT);
  esp_now_init();
  Serial.println("init");
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  /*if (newData = 1) {
    digitalWrite(2, HIGH);
    Serial.println("Lamp on");
  }
  //if (newData = 0) {
    digitalWrite(2, LOW);
    Serial.println("Lamp off");
  }
  delay(1000);
  */
}

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
  Serial.print("I just received -> ");
  Serial.println(*data);
  memcpy(&newData, data, sizeof(newData));
}