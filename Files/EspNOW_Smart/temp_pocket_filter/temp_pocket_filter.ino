/*****************************************************************************/
//  HighLevelExample.ino
//  Hardware:      Grove - 6-Axis Accelerometer&Gyroscope
//	Arduino IDE:   Arduino-1.65
//	Author:	       Lambor
//	Date: 	       Oct,2015
//	Version:       v1.0
//
//  Modified by:
//  Data:
//  Description:
//
//	by www.seeedstudio.com
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
/*******************************************************************************/
float temp1;
float temp2;

float avr1;
float tavr1;

float avr2;
float tavr2;

int tempfirst = 1;
int tempsec;

float avg_inc;
int avg_calc;

#include "LSM6DS3.h"
#include "Wire.h"

//Create a instance of class LSM6DS3
LSM6DS3 myIMU(I2C_MODE, 0x6A);  //I2C device address 0x6A

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial)
    ;
  //Call .begin() to configure the IMUs
  if (myIMU.begin() != 0) {
    Serial.println("Device error");
  } else {
    Serial.println("Device OK!");
  }
}

void loop() {
  for (int i = 0; i < 21; i++) {
    temp1 = myIMU.readTempC();
    avr1 += temp1;
    if (i == 20) {
      tavr1 = avr1 / 20;
      Serial.print("\nThermometer:\n");
      Serial.print(" Degrees C1 = ");
      Serial.println(tavr1, 4);
    }
    delay(50);
  }
  for (int j = 0; j < 21; j++) {
    temp2 = myIMU.readTempC();
    avr2 += temp2;
    if (j == 20) {
      tavr2 = avr2 / 20;
      Serial.print("\nThermometer:\n");
      Serial.print(" Degrees C2 = ");
      Serial.println(tavr2, 4);
    }
    delay(200);
  }
  avg_inc = tavr2 - tavr1;
  Serial.println(avg_inc);
  avr2 = 0;
  avr1 = 0;

  /*
  for (int i = 0; i < 21; i++) {
    if (tempfirst == 1) {
      temp1 = myIMU.readTempC();
      avr1 += temp1;
      if (i == 20) {
        tavr1 = avr1 / 20;
        Serial.print("\nThermometer:\n");
        Serial.print(" Degrees C1 = ");
        Serial.println(tavr1, 4);
        tempfirst = 0;
        tempsec = 1;
        i = 0;
      }
    }
    if (tempsec == 1) {
      temp2 = myIMU.readTempC();
      avr2 += temp2;
      if (i == 20) {
        tavr2 = avr2 / 20;
        Serial.print("\nThermometer:\n");
        Serial.print(" Degrees C2 = ");
        Serial.println(tavr2, 4);
        tempfirst = 0;
        tempsec = 0;
        avg_calc = 1;
        i = 0;
      }
    }
    if (avg_calc == 1) {
      avg_inc = tavr2 - tavr1;
      Serial.println(avg_inc);
      avr2 = 0;
      avr1 = 0;
      avg_calc = 0;
      tempfirst = 1;
      i = 0;
    }
    delay(50);
  }


  /*
  Serial.print("\nThermometer:\n");
  Serial.print(" Degrees C1 = ");
  Serial.println(myIMU.readTempC(), 4);
  Serial.print(" Degrees F1 = ");
  Serial.println(myIMU.readTempF(), 4);

  delay(1000);
  */
}
