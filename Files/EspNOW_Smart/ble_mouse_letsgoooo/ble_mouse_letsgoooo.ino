#include <BleCombo.h>
String leerlingnum = "144445";
String password = "M.8H.9lb";

void setup() {
  Serial.begin(115200);
  pinMode(3, INPUT_PULLUP);
  Serial.println("Starting work!");
  Keyboard.begin();
  Mouse.begin();
}

void loop() {
  if (Keyboard.isConnected()) {
    int buttonval = digitalRead(3);
    Serial.println(buttonval);
    if (buttonval == 0) {
      signing_in();
      move_mouse();
      //Serial.println("Sending Play/Pause media key...");
      //Keyboard.write(KEY_MEDIA_PLAY_PAUSE);

      //Serial.println("Sending Ctrl+Alt+Delete...");
      //Keyboard.press(KEY_LEFT_CTRL);
      // Keyboard.press(KEY_LEFT_ALT);
      // Keyboard.press(KEY_DELETE);
      // delay(100);
      //Keyboard.releaseAll();

      // Serial.println("Move mouse pointer up");


      //Mouse.move(10,10);
      // Mouse.move(0,-10);

      //Serial.println("Scroll Down");
      //Mouse.move(0,0,-1);

      //Serial.println("Left click");
      //Mouse.click(MOUSE_LEFT);
    }
  }

  //Serial.println("Waiting 2 seconds...");
  delay(500);
}

void signing_in() {
  Serial.println("signing in");
  Keyboard.println(password);
  Keyboard.write(KEY_RETURN);
  delay(10000);

  Serial.println("greating a new tab");
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.println("t");
  delay(3000);
  Keyboard.releaseAll();

  Serial.println("shearshing for magister");
  Keyboard.println("esdal.magister.net");
  delay(500);
  Serial.println("Sending Enter key...");
  Keyboard.write(KEY_RETURN);
  delay(3000);

  Serial.println("typing leerling num");
  Keyboard.println(leerlingnum);
  delay(500);
  Keyboard.write(KEY_RETURN);
  delay(500);

  Serial.println("typing password");
  Keyboard.println(password);
  delay(500);
  Keyboard.write(KEY_RETURN);
  delay(2000);
}

void move_mouse() {
  for (int i = 0; i < 22; i++) {
    Serial.println(i);
    Mouse.move(-68, 38);
    if (i > 20) {
      continue;
    }
    delay(400);
  }
  Mouse.move(35, -35);
  Mouse.click(MOUSE_LEFT);
  delay(1000);
  Mouse.move(40, 0);
  Mouse.click(MOUSE_LEFT);
  delay(3000);
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.println("w");
  delay(1000);
  Keyboard.releaseAll();
}
