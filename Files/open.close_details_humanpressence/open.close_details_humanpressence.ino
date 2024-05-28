#include "Arduino.h"
#include <humanstaticLite.h>
#include <HardwareSerial.h>

//#include <SoftwareSerial.h>
// Choose any two pins that can be used with SoftwareSerial to RX & TX
//#define RX_Pin A2
//#define TX_Pin A3

//SoftwareSerial mySerial = SoftwareSerial(RX_Pin, TX_Pin);

// we'll be using software serial
//HumanStaticLite radar = HumanStaticLite(&mySerial);

// can also try hardware serial with
HardwareSerial MySerial0(0);
HumanStaticLite radar = HumanStaticLite(&Serial0);

const unsigned char close_buff[10] = {0x53, 0x59, 0x08, 0x00, 0x00, 0x01, 0x00, 0xB5, 0x54, 0x43};  //switch off Open Underlying Message
const unsigned char open_buff[10] = {0x53, 0x59, 0x08, 0x00, 0x00, 0x01, 0x01, 0xB6, 0x54, 0x43};   //switch on Open Underlying Message

const unsigned char set_noperson_time_buff[10] = {0x53, 0x59, 0x80, 0x8A, 0x00, 0x01, 0x00, 0x1B7, 0x54, 0x43};
const unsigned char set_sens_buff[10] = {0x53, 0x59, 0x05, 0x08, 0x00, 0x01, 0x01, 0xBB, 0x54, 0x43};
const unsigned char set_scene_buff[10] = {0x53, 0x59, 0x05, 0x07, 0x00, 0x01, 0x03, 0xBC, 0x54, 0x43};

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
  //Serial.println("trying");
  radar.checkSetMode_func(open_buff, 10, false);
  delay(50);   //Do not set the delay time too long, as this may affect the reception of the data frames returned by the radar.
}
