#include "Arduino.h"
#include <humanstaticLite.h>
#include <HardwareSerial.h>>
//#include <SoftwareSerial.h>
// Choose any two pins that can be used with SoftwareSerial to RX & TX
//#define RX_Pin A2
//#define TX_Pin A3

//SoftwareSerial mySerial = SoftwareSerial(RX_Pin, TX_Pin);

// we'll be using software serial
//HumanStaticLite radar = HumanStaticLite(&mySerial);
HardwareSerial MySerial0(0);
// can also try hardware serial with
HumanStaticLite radar = HumanStaticLite(&MySerial0);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  MySerial0.begin(115200, SERIAL_8N1, -1, -1);

  //  mySerial.begin(115200);

  while(!Serial);   //When the serial port is opened, the program starts to execute.

  Serial.println("Ready");
}

void loop() {
  // put your main code here, to run repeatedly:
   radar.recvRadarBytes();           //Receive radar data and start processing
  //radar.showData();                 //Serial port prints a set of received data frames
   Serial.print("Spatial static values: ");
        Serial.println(radar.static_val);

        Serial.print("Distance to stationary object: ");
        Serial.print(radar.dis_static);
        Serial.println(" m");

        Serial.print("Spatial dynamic values: ");
        Serial.println(radar.dynamic_val);
        
        Serial.print("Distance from the movement object: ");
        Serial.print(radar.dis_move);
        Serial.println(" m");

        Serial.print("Speed of moving object: ");
        Serial.print(radar.speed);
        Serial.println(" m/s");
        Serial.println("---------------------------------");
  delay(200);                       //Add time delay to avoid program jam
}
