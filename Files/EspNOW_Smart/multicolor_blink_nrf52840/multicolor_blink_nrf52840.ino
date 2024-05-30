//The NRF52840 rgb led uses a not gate to drive the leds, so high = led_off and low = led_on
//The analog rgb also is infurtud so 255 is 0 and 0 = 255


//all optional fuctions:
//Red_Green_Blue_Test();
//Led_Bounce();
//Led_Middle_Bounce();
//Red_Blink();
//Green_Blink();
//Blue_Blink();
//Yellow_Blink();
//Purple_Blink();
//BlueGreen_Blink();
//Wite_Blink();
//All_Colours_Blink();
//LED_OFF();
//RED_ON();
//GREEN_ON();
//BLUE_ON();
//YELLOW_ON();
//PURPLE_ON();
//BLUEGREEN_ON();
//WITE_ON();
//DIM_RED();
//DIM_GREEN();
//DIM_BLUE();
//RGB_LED();
//Millis_Blink_RED();
//Millis_Blink_GREEN();
//Millis_Blink_BLUE();


#define RED_BLINK_DURATION 1000
#define GREEN_BLINK_DURATION 1000
#define BLUE_BLINK_DURATION 1000


#define YELLOW_BLINK_DURATION 1000
#define PURPLE_BLINK_DURATION 1000
#define BLUEGREEN_BLINK_DURATION 1000
#define WITE_BLINK_DURATION 1000


#define LED_BOUNCE_DURATION 250
#define LED_BOUNCE_PAUSE 750


#define LED_MAX_DIM 255


unsigned long previousMillis = 0;
unsigned long currentMillis;
int led_state = LOW;
int Red = 0;
int Green = 1;
int Blue = 1;


int count = 0;
void setup() {
  Serial.begin(115200);
  pinMode(LED_RED, OUTPUT);    //red light output
  pinMode(LED_BLUE, OUTPUT);   // bluee light output
  pinMode(LED_GREEN, OUTPUT);  //green light output
}




void loop() {
  Blink_Order(3);
  /*
 Millis_Blink_RED();
 Millis_Blink_GREEN();
 Millis_Blink_BLUE();
 Serial.println(millis());
*/
}
void Blink_Order(int num_fuctions) {
  switch (count) {
    case 0:
      Millis_Blink_RED();
      break;
    case 1:
      Millis_Blink_GREEN();
      break;
    case 2:
      Millis_Blink_BLUE();
      break;
  }
  if (count == num_fuctions) {
    count = 0;
  }
  else{
    Serial.println(count);
  }
}
//TEST AL THE COLOURS;
void Red_Green_Blue_Test() {
  Red_Blink();
  Green_Blink();
  Blue_Blink();
}
void All_Colours_Blink() {
  Red_Blink();
  Green_Blink();
  Blue_Blink();
  Yellow_Blink();
  Purple_Blink();
  BlueGreen_Blink();
  Wite_Blink();
}


//  PATERNS:
void Led_Bounce() {
  RED_ON();
  delay(LED_BOUNCE_PAUSE);
  LED_OFF();
  delay(LED_BOUNCE_DURATION);


  GREEN_ON();
  delay(LED_BOUNCE_DURATION);
  BLUE_ON();
  delay(LED_BOUNCE_PAUSE);




  LED_OFF();
  delay(LED_BOUNCE_DURATION);
  GREEN_ON();
  delay(LED_BOUNCE_DURATION);
}
void Led_Middle_Bounce() {
  digitalWrite(LED_RED, LOW);     // RED HIGH
  digitalWrite(LED_GREEN, HIGH);  // GREEN LOW
  digitalWrite(LED_BLUE, LOW);    // BLUE HIGH
  delay(LED_BOUNCE_PAUSE);


  digitalWrite(LED_RED, HIGH);   // RED LOW
  digitalWrite(LED_GREEN, LOW);  // GREEN HIGH
  digitalWrite(LED_BLUE, HIGH);  // BLUE LOW
  delay(LED_BOUNCE_PAUSE);
}
// MILIS() blink:

void Millis_Blink_RED() {
  currentMillis = millis();
  if (currentMillis - previousMillis >= RED_BLINK_DURATION) {
    previousMillis = currentMillis;
    if (led_state == LOW) {
      RED_ON();
      //Serial.println("red led on");
      led_state = HIGH;
    } else {
      LED_OFF();
      //Serial.println("red led off");
      led_state = LOW;
      count += 1;
    }
  }
}


void Millis_Blink_GREEN() {
  currentMillis = millis();
  if (currentMillis - previousMillis >= GREEN_BLINK_DURATION) {
    previousMillis = currentMillis;
    if (led_state == LOW) {
      GREEN_ON();
      //Serial.println("green led on");
      led_state = HIGH;
    } else {
      LED_OFF();
      //Serial.println("green led off");
      led_state = LOW;
      count += 1;
    }
  }
}
void Millis_Blink_BLUE() {
  currentMillis = millis();
  if (currentMillis - previousMillis >= BLUE_BLINK_DURATION) {
    previousMillis = currentMillis;
    if (led_state == LOW) {
      BLUE_ON();
      // Serial.println("blue led on");
      led_state = HIGH;
    } else {
      LED_OFF();
      //Serial.println("blue led off");
      led_state = LOW;
      count += 1;
    }
  }
}
//COLORS BLINK:
void Red_Blink() {
  RED_ON();
  delay(RED_BLINK_DURATION);
  LED_OFF();
  delay(RED_BLINK_DURATION);
}
void Green_Blink() {
  GREEN_ON();
  delay(GREEN_BLINK_DURATION);
  LED_OFF();
  delay(GREEN_BLINK_DURATION);
}
void Blue_Blink() {
  BLUE_ON();
  delay(BLUE_BLINK_DURATION);
  LED_OFF();
  delay(BLUE_BLINK_DURATION);
}
void Yellow_Blink() {
  YELLOW_ON();
  delay(YELLOW_BLINK_DURATION);
  LED_OFF();
  delay(YELLOW_BLINK_DURATION);
}
void Purple_Blink() {
  PURPLE_ON();
  delay(PURPLE_BLINK_DURATION);
  LED_OFF();
  delay(PURPLE_BLINK_DURATION);
}
void BlueGreen_Blink() {
  BLUEGREEN_ON();
  delay(BLUEGREEN_BLINK_DURATION);
  LED_OFF();
  delay(BLUEGREEN_BLINK_DURATION);
}
void Wite_Blink() {
  WITE_ON();
  delay(WITE_BLINK_DURATION);
  LED_OFF();
  delay(WITE_BLINK_DURATION);
}


// RGB COLORS ON:
void LED_OFF() {
  digitalWrite(LED_BLUE, HIGH);   // BLUE LOW
  digitalWrite(LED_GREEN, HIGH);  // GREEN LOW
  digitalWrite(LED_RED, HIGH);    // RED LOW
}
void RED_ON() {
  digitalWrite(LED_BLUE, HIGH);   //GREEN LOW
  digitalWrite(LED_GREEN, HIGH);  // GREEN LOW
  digitalWrite(LED_RED, LOW);     // RED HIGH
}
void GREEN_ON() {
  digitalWrite(LED_RED, HIGH);   // RED LOW
  digitalWrite(LED_BLUE, HIGH);  // RED LOW
  digitalWrite(LED_GREEN, LOW);  // GREEN HIGH
}
void BLUE_ON() {
  digitalWrite(LED_RED, HIGH);    // RED LOW
  digitalWrite(LED_GREEN, HIGH);  // GREEN LOW
  digitalWrite(LED_BLUE, LOW);    // BLUE HIGH
}


// DIMM RGB
void DIM_RED() {
  for (int i = 0; i < (LED_MAX_DIM + 1); i++) {
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_GREEN, HIGH);
    analogWrite(LED_RED, i);
    Serial.println(i);
    if (i >= LED_MAX_DIM) {
      i = 0;
    }
    delay(100);
  }
}


void DIM_GREEN() {
  for (int i = 0; i < (LED_MAX_DIM + 1); i++) {
    digitalWrite(LED_BLUE, HIGH);  // BLUE LOW
    digitalWrite(LED_RED, HIGH);   // RED LOW
    analogWrite(LED_GREEN, i);     // VARIABLE
    Serial.println(i);
    if (i >= LED_MAX_DIM) {
      i = 0;
    }
    delay(100);
  }
}


void DIM_BLUE() {
  for (int i = 0; i < (LED_MAX_DIM + 1); i++) {
    digitalWrite(LED_RED, HIGH);    // RED LOW
    digitalWrite(LED_GREEN, HIGH);  //GREEN LOW
    analogWrite(LED_BLUE, i);       // VARIABLE
    Serial.println(i);
    if (i >= LED_MAX_DIM) {
      i = 0;
    }
    delay(100);
  }
}
void RGB_LED(int R, int G, int B) {
  analogWrite(LED_RED, R);
  analogWrite(LED_GREEN, G);
  analogWrite(LED_BLUE, B);
}
//COMBINATION COLLORS:
void YELLOW_ON() {
  digitalWrite(LED_RED, LOW);    // RED HIGH
  digitalWrite(LED_GREEN, LOW);  // GREEN HIGH
  digitalWrite(LED_BLUE, HIGH);  // BLUE LOW
}
void PURPLE_ON() {
  digitalWrite(LED_RED, LOW);     // RED HIGH
  digitalWrite(LED_GREEN, HIGH);  // GREEN LOW
  digitalWrite(LED_BLUE, LOW);    // BLUE HIGH
}
void BLUEGREEN_ON() {
  digitalWrite(LED_RED, HIGH);   // RED LOW
  digitalWrite(LED_GREEN, LOW);  // GREEN HIGH
  digitalWrite(LED_BLUE, LOW);   // BLUE HIGH
}
void WITE_ON() {
  digitalWrite(LED_RED, LOW);    // RED HIGH
  digitalWrite(LED_GREEN, LOW);  // GREEN HIGH
  digitalWrite(LED_BLUE, LOW);   // BLUE HIGH
}
