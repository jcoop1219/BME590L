// parameters
const int flashRateHz = 2;
const int pwmMax = 255;
const int debounceDelayMs = 50;
const int lowBatteryVoltage = 7.5;
const int medBatteryVoltage = 8.5;

// I/O pins
const int buttonIn = 20;
const int whiteLEDout = 21;
const int greenLEDout = 28;
const int redLEDout = 29;
const int blueLEDout = 30;
const int batteryVoltageIn = 4;

// global variables
int mode = 0;
bool buttonPushed = true;
int pwmOut = 0;
bool prevButtonState = true;
int lastDebounceTime = 0;
int batteryVoltage = 0;


void setup() {
  attachInterrupt(digitalPinToInterrupt(buttonIn),detectButtonPress,CHANGE);
}

void loop() {
  setMode();
  outputLight();
  checkBattery();
  outputBatteryIndicator();
}

void detectButtonPress() {
  buttonPushed = !buttonPushed;
}

void setMode() {
  if (buttonPushed != prevButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelayMs) {
    if (mode = 4) {
      mode = 0;
    }
    else {
      ++mode;
    }
  }
  prevButtonState = buttonPushed;
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
  else if (batteryVoltage < (102.4*lowBatteryVoltage)) {
    digitalWrite(redLEDout,HIGH);
    digitalWrite(blueLEDout,LOW);
    digitalWrite(greenLEDout,LOW);
  }
  else if (batteryVoltage < (102.4*medBatteryVoltage)) {
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
