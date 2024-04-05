#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif

void setup(){
  Serial.begin(115200);
  Serial.println();
  while(Serial != true){delay(10);}
  Serial.print("ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());//get mac adress
}
 
void loop(){

}
