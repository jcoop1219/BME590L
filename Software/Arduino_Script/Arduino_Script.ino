// parameters
const int flashRateHz = 2;
const int pwmMax = 255;
const int debounceDelayMs = 100;
const float lowBatteryVoltage = 7.5;
const float medBatteryVoltage = 8.5;

// I/O pins
const int buttonIn = 2;
const int whiteLEDout = 3;
const int greenLEDout = 10;
const int redLEDout = 11;
const int blueLEDout = 12;
const float batteryVoltageIn = 0;

// global variables
int mode = 0;
bool buttonPushed = false;
int pwmOut = 0; //0-255
//bool prevButtonState = false;
int lastDebounceTime = 0;
int batteryVoltage = 0;


void setup() {
  pinMode(whiteLEDout,OUTPUT);
  pinMode(redLEDout,OUTPUT);
  pinMode(greenLEDout,OUTPUT);
  pinMode(blueLEDout,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(buttonIn),detectButtonPress,RISING);
  
}

void loop() {
  setMode();
  outputLight();
  checkBattery();
  outputBatteryIndicator();
}

void detectButtonPress() {
  if ((millis() - lastDebounceTime) > debounceDelayMs) {
    buttonPushed = true;
    lastDebounceTime = millis();
  }
}

void setMode() {
  if (buttonPushed) {
    if (mode == 4) {
      mode = 0;
    }
    else {
      ++mode;
    }
    buttonPushed = false;
  }
}

//void outputLight() {
//  if (mode == 0) {
//    digitalWrite(whiteLEDout,HIGH);
//  }
//  else {
//    digitalWrite(whiteLEDout,LOW);
//  }
//}

void outputLight() {
  switch (mode) {
    case 0:
      pwmOut = 0;
      shineLED();
      break;
    case 1:
      pwmOut = pwmMax;
      shineLED();
      break;
    case 2:
      pwmOut = int(pwmMax/2);
      shineLED();
      break;
    case 3:
      pwmOut = int(pwmMax/4);
      shineLED();
      break;
    case 4:
      flashLED();
      break;
  }
}

void shineLED() {
  analogWrite(whiteLEDout,pwmOut);
}

void flashLED() {
  digitalWrite(whiteLEDout,HIGH);
  delay(500/flashRateHz);
  digitalWrite(whiteLEDout,LOW);
  delay(500/flashRateHz);
}

void checkBattery() {
  batteryVoltage = analogRead(batteryVoltageIn);
}

void outputBatteryIndicator() {
  if (batteryVoltage < 100) {
    digitalWrite(redLEDout,LOW);
    digitalWrite(blueLEDout,LOW);
    digitalWrite(greenLEDout,LOW);
  }
  else if (batteryVoltage < (204.8*(lowBatteryVoltage*0.497))) {  // in voltage divider, theoretical 7.5V is dropped 3.75V then 3.71V, and 0.497 = (3.71/(3.71+3.75))
    digitalWrite(redLEDout,HIGH);
    digitalWrite(blueLEDout,LOW);
    digitalWrite(greenLEDout,LOW);
  }
  else if (batteryVoltage < (204.8*(medBatteryVoltage*0.493))) { // in voltage divider, theoretical 8.5V is dropped 4.28V then 4.17V, and 0.493 = (4.17/(4.17+4.28))
    digitalWrite(redLEDout,LOW);
    digitalWrite(blueLEDout,HIGH);
    digitalWrite(greenLEDout,LOW);
  }
  else {
    digitalWrite(redLEDout,LOW);
    digitalWrite(blueLEDout,LOW);
    digitalWrite(greenLEDout,HIGH);
  }
}
