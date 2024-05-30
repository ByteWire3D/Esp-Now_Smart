#include <esp_now.h>
#include <WiFi.h>

#define BUTTON_PIN_BITMASK 0x200000000
#define CHANNEL 1

esp_now_peer_info_t slave;
int door;

uint8_t receiverAddress[]{ 0xEC, 0xDA, 0x3B, 0xAA, 0xA0, 0x04 };
//uint8_t receiverAddress[]{EC:DA:3B:AA:A0:04};
// 0xEC, 0xDA, 0x3B, 0xAA, 0xA0, 0x04
// mac: EC:DA:3B:AA:A0:04

uint8_t msg;
void setup() {
  Serial.begin(115200);
  Serial.println("serial port open");
  pinMode(3, INPUT);
  WiFi.mode(WIFI_STA);
  esp_now_init();
  Serial.println("espnow init");
  slave.channel = CHANNEL;
  slave.encrypt = 0;
  esp_now_add_peer(&slave);
  Serial.println(" data callbank on its way: ");
  esp_now_register_send_cb(OnDataSent);
  // Serial.println(door);
  //msg = 1;
  //esp_now_send(receiverAddress, &msg, sizeof(msg));
}
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t sendStatus) {
  //Serial.print("fucking say somethn");
  if (sendStatus == 1) {
    Serial.println("sending succes!");
    /* success */
  }

  if (sendStatus == 0) {
    Serial.println("sending fail :(");
    /* fail */
  }
}
void deepsleep_logic() {
  door = digitalRead(3);
  if (door = 1) {
    msg = door;
    Serial.print(msg);
    /// Serial.print("  \   ");
    //Serial.print(door);
    Serial.println();
    // door = 0;
    // esp_deep_sleep_enable_gpio_wakeup(BIT(D1), ESP_GPIO_WAKEUP_GPIO_LOW);
    esp_now_send(receiverAddress, &msg, sizeof(msg));
    esp_now_register_send_cb(OnDataSent);
    //esp_deep_sleep_start();
  }
  if (door = 0) {
    msg = door;
    Serial.print(msg);
    /// Serial.print("  \   ");
    //Serial.print(door);
    Serial.println();
    // door = 1;
    //esp_deep_sleep_enable_gpio_wakeup(BIT(D1), ESP_GPIO_WAKEUP_GPIO_HIGH);
    esp_now_send(receiverAddress, &msg, sizeof(msg));
    esp_now_register_send_cb(OnDataSent);
    // esp_deep_sleep_start();
  }
}
void loop() {
  const uint8_t *peer_addr = receiverAddress;
  msg = 1;
  esp_now_send(peer_addr, &msg, sizeof(msg));
  esp_now_register_send_cb(OnDataSent);
  Serial.println("door open");

  delay(1000);
  msg = 0;
  esp_now_send(peer_addr, &msg, sizeof(msg));
  esp_now_register_send_cb(OnDataSent);
  Serial.println("door closed");


  delay(1000);
  //deepsleep_logic();
}
