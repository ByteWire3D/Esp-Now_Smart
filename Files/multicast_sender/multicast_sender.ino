#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t repeater_adress[] = { 0xEC, 0xDA, 0x3B, 0xAA, 0xC3, 0xA0 };
//EC:DA:3B:AA:C3:A0
// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  char next[32];
  char data[32];
  float vBat;

} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if(status== ESP_NOW_SEND_SUCCESS){
     digitalWrite(3, HIGH);
      delay(2000);
      digitalWrite(3, LOW);
  }
}

void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  digitalWrite(3, HIGH);
  delay(2000);
  digitalWrite(3, LOW);
  WiFi.mode(WIFI_STA);  // Set device as a Wi-Fi Station

  if (esp_now_init() != ESP_OK) {  // Init ESP-NOW
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet

  // Register peer
  memcpy(peerInfo.peer_addr, repeater_adress, 6);
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
  strcpy(myData.next, "repeater2");
  strcpy(myData.data, "Door_open");
  // Send message via ESP-NOW
  //get_vbat();
  esp_err_t result = esp_now_send(repeater_adress, (uint8_t *)&myData, sizeof(myData));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
    digitalWrite(4, HIGH);
    delay(2000);
    digitalWrite(4, LOW);
  } else {
    Serial.println("Error sending the data");
  }
  delay(2000);

  //myData.d = true;
  strcpy(myData.next, "bedroom");
  strcpy(myData.data, "Door_closed");
  // Send message via ESP-NOW
  result = esp_now_send(repeater_adress, (uint8_t *)&myData, sizeof(myData));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
    digitalWrite(4, HIGH);
    delay(2000);
    digitalWrite(4, LOW);
  } else {
    Serial.println("Error sending the data");
  }
  delay(2000);
}
void get_vbat() {
  int read = analogRead(2);
  Serial.println(read);
  float Bat_voltage = map(read, 0, 4095, 0, 2.5);

  myData.vBat = Bat_voltage * 2;
}
