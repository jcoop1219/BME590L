// parameters
const int flashRateHz = 2;  //rate of blinking for flash mode
const int pwmMax = 255;  //max threshold for PWM signal
const int debounceDelayMs = 100;  //debounce on main button
const float deadBatteryVoltage = 5.4;  //threshold for dead battery
const float lowBatteryVoltage = 7;  //threshold for low voltage on battery
const float medBatteryVoltage = 8;  //threshold for med voltage on battery
const float conversionFactor = 100.8; //used to convert battery voltage thresholds to 0-1023 digital range read-in via voltage divider circuit

// I/O pins
const int buttonIn = 2;  //main button digital in
const int whiteLEDout = 3;  //main LED digital out
const int greenLEDout = 10;  //battery tester LED digital out
const int redLEDout = 11;  //battery tester LED digital out
const int blueLEDout = 12;  //battery tester LED digital out
const int batteryVoltageIn = 0;  //battery tester analog in

// global variables
int mode = 0;  //flashing mode
bool buttonPushed = false;
int pwmOut = 0; //0-255 PWM signal
unsigned long lastDebounceTime = 0;
int batteryVoltage = 0;
unsigned long lastFlashTime = 0;
bool flashMode = LOW;


void setup() {
  pinMode(whiteLEDout,OUTPUT);
  pinMode(redLEDout,OUTPUT);
  pinMode(greenLEDout,OUTPUT);
  pinMode(blueLEDout,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(buttonIn),detectButtonPress,RISING);
  
}

void loop() {
  setMode();  //sets flashing mode
  outputLight();  //outputs light based on flashing mode
  checkBattery();  //checks battery voltage
  outputBatteryIndicator();  //outputs to RBG LED based on battery voltage remaining
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
    case 0:  //off
      pwmOut = 0;
      shineLED();
      break;
    case 1:  //full brightness
      pwmOut = pwmMax;
      shineLED();
      break;
    case 2:  //medium brightness
      pwmOut = int(pwmMax/2);
      shineLED();
      break;
    case 3:  //low brightness
      pwmOut = int(pwmMax/4);
      shineLED();
      break;
    case 4:  //flashing
      flashLED();
      break;
  }
}

void shineLED() {
  analogWrite(whiteLEDout,pwmOut);
}

void flashLED() {
  if ((millis() - lastFlashTime) >= (500/flashRateHz)) {
    flashMode = !flashMode;
    digitalWrite(whiteLEDout,flashMode);
    lastFlashTime = millis();
  }
}

void checkBattery() {
  batteryVoltage = analogRead(batteryVoltageIn);
}

void outputBatteryIndicator() {
  if (batteryVoltage < (deadBatteryVoltage*conversionFactor)) {  //battery votlage < 5.4V is dead
    digitalWrite(redLEDout,LOW);
    digitalWrite(blueLEDout,LOW);
    digitalWrite(greenLEDout,LOW);
  }
  else if (batteryVoltage < (lowBatteryVoltage*conversionFactor)) {  //battery voltage < 7V is low
    digitalWrite(redLEDout,HIGH);
    digitalWrite(blueLEDout,LOW);
    digitalWrite(greenLEDout,LOW);
  }
  else if (batteryVoltage < (medBatteryVoltage*conversionFactor)) {  //battery voltage < 8V is medium
    digitalWrite(redLEDout,LOW);
    digitalWrite(blueLEDout,HIGH);
    digitalWrite(greenLEDout,LOW);
  }
  else {  //battery voltage >=8V is high
    digitalWrite(redLEDout,LOW);
    digitalWrite(blueLEDout,LOW);
    digitalWrite(greenLEDout,HIGH);
  }
}
