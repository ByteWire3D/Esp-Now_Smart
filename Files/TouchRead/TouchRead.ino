// ESP32 Touch Test
// Just test touch pin - Touch0 is T0 which is on GPIO 4.
int touch_2_ref;
int touch_3_ref;
int touch_8_ref;
int touch_9_ref;

int touch_2;
int touch_3;
int touch_8;
int touch_9;

int treshhold = 1500;
int touch_tresh = 2500;
int hover_tresh = 1000;
void setup() {
  Serial.begin(115200);
  delay(1000);  // give me time to bring up serial monitor
  Serial.println("ESP32 Touch Test");
  mesure_ref_touch();
  calibrate_touch();
}

void loop() {
  Serial.print("touch 2: ");
  Serial.print(touch_2 - touchRead(T2));  // get value using T1
  Serial.print(",");
  Serial.print("touch 3: ");
  Serial.print(touch_3 - touchRead(T3));  // get value using T1
  Serial.print(",");
  Serial.print("touch 8: ");
  Serial.print(touch_8 - touchRead(T8));  // get value using T1
  Serial.print(",");
  Serial.print("touch 9: ");
  Serial.println(touch_9 - touchRead(T9));  // get value using T1


  delay(50);
}

void mesure_ref_touch() {
  for (int count = 0; count < 11; count++) {
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
    delay(10);
  }
  touch_2_ref = touch_2_ref / 10;
  touch_3_ref = touch_3_ref / 10;
  touch_8_ref = touch_8_ref / 10;
  touch_9_ref = touch_9_ref / 10;
}
void calibrate_touch() {
  int state = 0;
  switch (state) {
    case 0:
      while ((touchRead(T2) - touch_2_ref) <= treshhold || (touchRead(T2) - touch_2_ref) > 4000000000) {
        Serial.print("not touch detected on touch 2??");
        Serial.print("\t");
        Serial.print("reason: ");
        Serial.println((touchRead(T2) - touch_2_ref));
        delay(10);
      }
      if ((touchRead(T2) - touch_2_ref) >= treshhold && (touchRead(T2) - touch_2_ref) < 4294964484) {
        for (int i = 0; i < 11; i++) {
          touch_2 += touchRead(T2);
          Serial.print("reading touch2: ");
          Serial.print(touch_2);
          Serial.print("\t");
          Serial.println((touchRead(T2) - touch_2_ref));
          delay(50);
        }
        touch_2 = touch_2 / 10;
        state = 1;
        //break;
      }
    case 1:
      while ((touchRead(T3) - touch_3_ref) <= treshhold || (touchRead(T3) - touch_3_ref) > 4000000000) {
        Serial.print("not touch detected on touch 3??");
        Serial.print("\t");
        Serial.print("reason: ");
        Serial.println((touchRead(T3) - touch_3_ref));
        delay(10);
      }
      if ((touchRead(T3) - touch_3_ref) >= treshhold && (touchRead(T3) - touch_3_ref) < 4294964484) {
        for (int j = 0; j <= 10; j++) {
          touch_3 += touchRead(T3);
          Serial.print("reading touch3: ");
          Serial.print(touch_3);
          Serial.print("\t");
          Serial.println((touchRead(T3) - touch_3_ref));
          delay(50);
        }
        touch_3 = touch_3 / 10;
        state = 2;
        //break;
      }
    case 2:
      while ((touchRead(T8) - touch_8_ref) <= treshhold || (touchRead(T8) - touch_8_ref) > 4000000000) {
        Serial.print("not touch detected on touch 8??");
        Serial.print("\t");
        Serial.print("reason: ");
        Serial.println((touchRead(T8) - touch_8_ref));
        delay(10);
      }
      if ((touchRead(T8) - touch_8_ref) >= treshhold && (touchRead(T8) - touch_8_ref) < 4294964484) {
        for (int k = 0; k <= 10; k++) {
          Serial.print("reading touch8: ");
          Serial.print(touch_8);
          Serial.print("\t");
          Serial.println((touchRead(T8) - touch_8_ref));
          touch_8 += touchRead(T8);
          delay(50);
        }
        touch_8 = touch_8 / 10;
        state = 3;
        //break;
      }
    case 3:
      while ((touchRead(T9) - touch_9_ref) <= treshhold || (touchRead(T9) - touch_9_ref) > 4000000000) {
        Serial.print("not touch detected on touch 9??");
        Serial.print("\t");
        Serial.print("reason: ");
        Serial.println((touchRead(T9) - touch_9_ref));
        delay(10);
      }
      if ((touchRead(T9) - touch_9_ref) >= treshhold && (touchRead(T9) - touch_9_ref) < 4294964484) {
        for (int l = 0; l <= 10; l++) {
          Serial.print("reading touch9: ");
          Serial.print(touch_9);
          Serial.print("\t");
          Serial.println((touchRead(T9) - touch_9_ref));
          touch_9 += touchRead(T9);
          delay(50);
        }
        touch_9 = touch_9 / 10;
        state = 4;
        break;
      }
  }
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
  delay(2000);
}