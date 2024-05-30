// ESP32 Touch Test
// Just test touch pin - Touch0 is T0 which is on GPIO 4.
int touch_2_ref = 25886;
int touch_3_ref = 28264;
int touch_8_ref = 27866;
int touch_9_ref = 28243;

int touch_2;
int touch_3;
int touch_8;
int touch_9;

int ref_touch = 0;
int touch = 36452;

int treshhold_2 = 3000;
int treshhold_3 = 3000;
int treshhold_8 = 3000;
int treshhold_9 = 3000;
void setup() {
  Serial.begin(115200);
  delay(1000);  // give me time to bring up serial monitor
  Serial.println("ESP32 Touch Test");
  // mesure_ref_touch();
  //calibrate_touch();
}

void loop() {

  //print_touch();
  on_touch();
  //test_touch();
  delay(25);
}

void mesure_ref_touch() {
  if (ref_touch == 0) {
    for (int count = 0; count < 101; count++) {
      touch_2_ref += touchRead(T2);
      touch_3_ref += touchRead(T3);
      touch_8_ref += touchRead(T8);
      touch_9_ref += touchRead(T9);

      Serial.print("touch 2_ calibrate: ");
      Serial.print(touchRead(T2));  // get value using T1
      Serial.print(",");
      Serial.print("touch 3_calibrate: ");
      Serial.print(touchRead(T3));  // get value using T2
      Serial.print(",");
      Serial.print("touch 8_calibrate: ");
      Serial.print(touchRead(T8));  // get value using T3
      Serial.print("touch 9_calibrate: ");
      Serial.println(touchRead(T9));  // get value using T3
      delay(50);
    }
    touch_2_ref = touch_2_ref / 100;
    touch_3_ref = touch_3_ref / 100;
    touch_8_ref = touch_8_ref / 100;
    touch_9_ref = touch_9_ref / 100;
    Serial.print("touch_ref_2 = ");
    Serial.print(touch_2_ref);
    Serial.print("\t");
    Serial.print("touch_ref_3 = ");
    Serial.print(touch_3_ref);
    Serial.print("\t");
    Serial.print("touch_ref_4 = ");
    Serial.print(touch_8_ref);
    Serial.print("\t");
    Serial.print("touch_ref_9 = ");
    Serial.print(touch_9_ref);
    Serial.print("\n");
  }
}
void calibrate_touch() {
  if (touch == 0) {
    int state = 0;
    switch (state) {
      case 0:
        while ((touchRead(T2) - touch_2_ref) <= treshhold_2 || (touchRead(T2) - touch_2_ref) > 4000000000) {
          Serial.print("not touch detected on touch 2??");
          Serial.print("\t");
          Serial.print("reason: ");
          Serial.println((touchRead(T2) - touch_2_ref));
          delay(10);
        }
        if ((touchRead(T2) - touch_2_ref) >= treshhold_2 && (touchRead(T2) - touch_2_ref) < 4294964484) {
          for (int i = 0; i < 101; i++) {
            touch_2 += touchRead(T2);
            Serial.print("reading touch2: ");
            Serial.print(touch_2);
            Serial.print("\t");
            Serial.println((touchRead(T2) - touch_2_ref));
            delay(50);
          }
          touch_2 = touch_2 / 100;
          state = 1;
          //break;
        }
      case 1:
        while ((touchRead(T3) - touch_3_ref) <= treshhold_3 || (touchRead(T3) - touch_3_ref) > 4000000000) {
          Serial.print("not touch detected on touch 3??");
          Serial.print("\t");
          Serial.print("reason: ");
          Serial.println((touchRead(T3) - touch_3_ref));
          delay(10);
        }
        if ((touchRead(T3) - touch_3_ref) >= treshhold_3 && (touchRead(T3) - touch_3_ref) < 4294964484) {
          for (int j = 0; j < 101; j++) {
            touch_3 += touchRead(T3);
            Serial.print("reading touch3: ");
            Serial.print(touch_3);
            Serial.print("\t");
            Serial.println((touchRead(T3) - touch_3_ref));
            delay(50);
          }
          touch_3 = touch_3 / 100;
          state = 2;
          //break;
        }
      case 2:
        while ((touchRead(T8) - touch_8_ref) <= treshhold_8 || (touchRead(T8) - touch_8_ref) > 4000000000) {
          Serial.print("not touch detected on touch 8??");
          Serial.print("\t");
          Serial.print("reason: ");
          Serial.println((touchRead(T8) - touch_8_ref));
          delay(10);
        }
        if ((touchRead(T8) - touch_8_ref) >= treshhold_8 && (touchRead(T8) - touch_8_ref) < 4294964484) {
          for (int k = 0; k < 101; k++) {
            Serial.print("reading touch8: ");
            Serial.print(touch_8);
            Serial.print("\t");
            Serial.println((touchRead(T8) - touch_8_ref));
            touch_8 += touchRead(T8);
            delay(50);
          }
          touch_8 = touch_8 / 100;
          state = 3;
          //break;
        }
      case 3:
        while ((touchRead(T9) - touch_9_ref) <= treshhold_9 || (touchRead(T9) - touch_9_ref) > 4000000000) {
          Serial.print("not touch detected on touch 9??");
          Serial.print("\t");
          Serial.print("reason: ");
          Serial.println((touchRead(T9) - touch_9_ref));
          delay(10);
        }
        if ((touchRead(T9) - touch_9_ref) >= treshhold_9 && (touchRead(T9) - touch_9_ref) < 4294964484) {
          for (int l = 0; l < 101; l++) {
            Serial.print("reading touch9: ");
            Serial.print(touch_9);
            Serial.print("\t");
            Serial.println((touchRead(T9) - touch_9_ref));
            touch_9 += touchRead(T9);
            delay(50);
          }
          touch_9 = touch_9 / 100;
          state = 4;
          break;
        }
    }
    touch = (touch_2 + touch_3 + touch_8 + touch_9) / 4;
    ref_touch = (touch_2_ref + touch_3_ref + touch_8_ref + touch_9_ref) / 4;
    Serial.print("touch 2:");
    Serial.print(touch_2);
    Serial.print("\t");
    Serial.print("touch 3:");
    Serial.print(touch_3);
    Serial.print("\t");
    Serial.print("touch 8:");
    Serial.print(touch_8);
    Serial.print("\t");
    Serial.print("touch 9:");
    Serial.print(touch_9);
    Serial.print("\n");
    Serial.print("touch_ref_2 = ");
    Serial.print(touch_2_ref);
    Serial.print("\t");
    Serial.print("touch_ref_3 = ");
    Serial.print(touch_3_ref);
    Serial.print("\t");
    Serial.print("touch_ref_4 = ");
    Serial.print(touch_8_ref);
    Serial.print("\t");
    Serial.print("touch_ref_9 = ");
    Serial.print(touch_9_ref);
    Serial.print("\n");
    Serial.print("ref touch ==");
    Serial.print(ref_touch);
    Serial.print("touch = ");
    Serial.println(touch);
    delay(5000);
  }
}
void print_touch() {
  Serial.print("touch 2: ");
  Serial.print(touchRead(T2));  // get value using T1
  Serial.print(",");
  Serial.print("touch 3: ");
  Serial.print(touchRead(T3));  // get value using T1
  Serial.print(",");
  Serial.print("touch 8: ");
  Serial.print(touchRead(T8));  // get value using T1
  Serial.print(",");
  Serial.print("touch 9: ");
  Serial.println(touchRead(T9));  // get value using T1
}
void on_touch() {
  touch_2 = touchRead(T2);
  touch_3 = touchRead(T3);
  touch_8 = touchRead(T8);
  touch_9 = touchRead(T9);

  touch_2 = constrain((touch_2 - touch_2_ref), 0, 100000);
  touch_3 = constrain((touch_3 - touch_3_ref), 0, 100000);
  touch_8 = constrain((touch_8 - touch_8_ref), 0, 100000);
  touch_9 = constrain((touch_9 - touch_9_ref), 0, 100000);

  if (touch_2 >= 3000) {
    Serial.print("left upp");
  }
  if (touch_2 >= 1500 && touch_9 >= 1500) {
    Serial.print("middel upp");
  }
  if (touch_9 >= 3000) {
    Serial.print("right upp");
  }
  if (touch_2 >= 1200 && touch_3 >= 1500) {
    Serial.print("middel left");
  }
  if (touch_2 >= 600 && touch_3 >= 500 && touch_8 >= 600 && touch_9 >= 1002) {
    Serial.print("middel ");
  }
  if (touch_8 >= 1400 && touch_9 >= 1200) {
    Serial.print("middel right");
  }
  if (touch_3 >= 3000) {
    Serial.print("bottom left");
  }
  if (touch_3 >= 1300 && touch_8 >= 1000) {
    Serial.print("bottom middel");
  }
  if (touch_8 >= 2800) {
    Serial.print("bottom right");
  }




  Serial.println();
}

void test_touch() {
  touch_2 = touchRead(T2);
  touch_3 = touchRead(T3);
  touch_8 = touchRead(T8);
  touch_9 = touchRead(T9);

  touch_2 = constrain((touch_2 - touch_2_ref), 0, 100000);
  touch_3 = constrain((touch_3 - touch_3_ref), 0, 100000);
  touch_8 = constrain((touch_8 - touch_8_ref), 0, 100000);
  touch_9 = constrain((touch_9 - touch_9_ref), 0, 100000);
  Serial.print(touch_2);
  Serial.print("\t");
  Serial.print(touch_3);
  Serial.print("\t");
  Serial.print(touch_8);
  Serial.print("\t");
  Serial.print(touch_9);
  Serial.println("\t");
}
