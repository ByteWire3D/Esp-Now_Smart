#include <esp_now.h>
#include <WiFi.h>  // EC:DA:3B:AA:A0:04
uint8_t bedroom_adress[] = { 0xEC, 0xDA, 0x3B, 0xAA, 0xA0, 0x04 };
//EC:DA:3B:AA:C4:78
uint8_t repeater2_adress[] = { 0xEC, 0xDA, 0x3B, 0xAA, 0xC4, 0x78 };

esp_now_peer_info_t peerInfo;

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  char next[32];
  char data[32];
  float vBat;
  //int b;
  //bool d;
} struct_message;

// Create a struct_message called myData
struct_message myData;
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status == ESP_NOW_SEND_SUCCESS) {
    digitalWrite(4, HIGH);
    delay(2000);
    digitalWrite(4, LOW);
  }
}
// callback function that will be executed when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  digitalWrite(3, HIGH);
  delay(2000);
  digitalWrite(3, LOW);
  memcpy(&myData, incomingData, sizeof(myData));

  //Serial.print("Bytes received: ");
 // Serial.println(len);
 // Serial.print("next destination: ");
 // Serial.println(myData.next);
 // Serial.print("data: ");
 // Serial.println(myData.data);
 // Serial.print("Vbat: ");
 // Serial.println(myData.vBat);
  // Serial.print("Int: ");
  // Serial.println(myData.b);
  //Serial.print("Bool: ");
  //Serial.println(myData.d);
 // Serial.println();
  
  if(String(myData.next) == "bedroom") {
    esp_err_t result = esp_now_send(bedroom_adress, (uint8_t *)&myData, sizeof(myData));

    if (result == ESP_OK) {
      Serial.println("Sent with success to the bedroom");


    } else {
      Serial.println("Error sending the data to the bedroom");
    }
  }
  
 
 if ( String(myData.next) == "repeater2") {
    Serial.println("trying to send the data.....");
    esp_err_t result = esp_now_send(repeater2_adress, (uint8_t *)&myData, sizeof(myData));
  
    if (result == ESP_OK) {
      Serial.println("Sent with success to the repeater");

    } else {
      Serial.println("Error sending the data to the repeater");
    }
  }
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  memcpy(peerInfo.peer_addr, repeater2_adress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  memcpy(peerInfo.peer_addr, bedroom_adress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;


  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
}