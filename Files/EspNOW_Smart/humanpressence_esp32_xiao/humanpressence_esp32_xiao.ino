#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t lamp_address[] = { 0xEC, 0xDA, 0x3B, 0xAA, 0xC1, 0x38 };
//EC:DA:3B:AA:C1:38
// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  char from[32];
  char data[32];

} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);  // Set device as a Wi-Fi Station
  pinMode(4, INPUT);
  pinMode(3, INPUT);
  if (esp_now_init() != ESP_OK) {  // Init ESP-NOW
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet

  // Register peer
  memcpy(peerInfo.peer_addr, lamp_address, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  // Set values to send
  bool ocupited = digitalRead(4);
  //bool moving = digitalRead(3);
  if (ocupited == true) {
    Serial.println("someone is in front of da sensor ");
    strcpy(myData.from, "human_pressence_bed");
    strcpy(myData.data, "someone in bed");
    esp_err_t result = esp_now_send(lamp_address, (uint8_t *)&myData, sizeof(myData));
  }
  if (ocupited == false) {
    Serial.println("no one in frame ");
    strcpy(myData.from, "human_pressence_bed");
    strcpy(myData.data, "no_one in bed");
    esp_err_t result = esp_now_send(lamp_address, (uint8_t *)&myData, sizeof(myData));
  }

  delay(1000);
}