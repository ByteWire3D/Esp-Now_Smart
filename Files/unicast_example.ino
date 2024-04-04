#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t lamp_reciever_address[] = {0xEC,0xDA,0x3B,0xAA,0xB9,0xCC};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  char a[32];
  //bool d;
  //int c;
  float vBat;
  
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

  WiFi.mode(WIFI_STA);// Set device as a Wi-Fi Station

  if (esp_now_init() != ESP_OK) { // Init ESP-NOW
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);// Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  
  // Register peer
  memcpy(peerInfo.peer_addr, lamp_reciever_address, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() {
  // Set values to send
  strcpy(myData.a, "off");
  // Send message via ESP-NOW
  get_vbat();
  esp_err_t result = esp_now_send(lamp_reciever_address, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(2000);

    //myData.d = true;
   strcpy(myData.a, "on");
  // Send message via ESP-NOW
   result = esp_now_send(lamp_reciever_address, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(2000);
}
void get_vbat(){
  int read = analogRead(2);
  Serial.println(read);
  float Bat_voltage = map(read,0, 4095,0, 2.5);
  
  myData.vBat = Bat_voltage *2;
}