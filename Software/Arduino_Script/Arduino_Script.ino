// parameters
const int flashRateHz = 2;
const int pwmMax = 255;
const int debounceDelayMs = 100;
const float deadBatteryVoltage = 5.4;
const float lowBatteryVoltage = 7;
const float medBatteryVoltage = 8;
const float conversionFactor = 100.8; //used to convert battery voltage thresholds to 0-1023 digital range read-in via voltage divider circuit
//const int batteryCheckDebounceMs = 250;

// I/O pins
const int buttonIn = 2;
const int whiteLEDout = 3;
const int greenLEDout = 10;
const int redLEDout = 11;
const int blueLEDout = 12;
const int batteryVoltageIn = 0;

// global variables
int mode = 0;
bool buttonPushed = false;
int pwmOut = 0; //0-255
int lastDebounceTime = 0;
int batteryVoltage = 0;
int lastBatteryCheckTime = 0;
int lastFlashTime = 0;
bool flashMode = LOW;


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

//void flashLED() {
//  digitalWrite(whiteLEDout,HIGH);
//  delay(500/flashRateHz);
//  digitalWrite(whiteLEDout,LOW);
//  delay(500/flashRateHz);
//}

void flashLED() {
  if ((millis() - lastFlashTime) >= (500/flashRateHz)) {
    flashMode = !flashMode;
    digitalWrite(whiteLEDout,flashMode);
    lastFlashTime = millis();
  }
}

//void checkBattery() {
//  if ((millis() - lastBatteryCheckTime) >= batteryCheckDebounceMs) {
//    batteryVoltage = analogRead(batteryVoltageIn);
//    lastBatteryCheckTime = millis();
//  }
//}

void checkBattery() {
  batteryVoltage = analogRead(batteryVoltageIn);
}

void outputBatteryIndicator() {
  if (batteryVoltage < (deadBatteryVoltage*conversionFactor)) {
    digitalWrite(redLEDout,LOW);
    digitalWrite(blueLEDout,LOW);
    digitalWrite(greenLEDout,LOW);
  }
  else if (batteryVoltage < (lowBatteryVoltage*conversionFactor)) {
    digitalWrite(redLEDout,HIGH);
    digitalWrite(blueLEDout,LOW);
    digitalWrite(greenLEDout,LOW);
  }
  else if (batteryVoltage < (medBatteryVoltage*conversionFactor)) {
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
