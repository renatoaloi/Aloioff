void resetBlink(int led) {
  int i = (led == LED2) ? 1 : 0;
  blinkRate[i] = millis();
}

void resetLedStatus(int led) {
  setLedStatus(led, false);
}

void setLedStatus(int led, bool val) {
  int i = (led == LED2) ? 1 : 0;
  blinkStatus[i] = false;
}

void setupLedPort(int led) {
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
}

void setupLeds() {
  resetBlink(LED1);
  resetBlink(LED2);
  resetLedStatus(LED1);
  resetLedStatus(LED2);
  setupLedPort(LED1);
  setupLedPort(LED2);
}

void blinkLed2Fast() {
  blinkLeds(LED2, 300);
}

void blinkLed2Slow() {
  blinkLeds(LED2, 1000);
}

void blinkLed1Fast() {
  blinkLeds(LED1, 200);
}

void blinkLeds(int led, int rate) {
  int i = (led == LED2) ? 1 : 0;
  if (blinkRate[i] + rate < millis()) {
    if (blinkStatus[i]) {
      blinkStatus[i] = false;
      turnOffLed(led);
    }
    else {
      blinkStatus[i] = true;
      turnOnLed(led);
    }
    resetBlink(led);
  }
}

void turnOnLed(int led) {
  digitalWrite(led, LOW);
}

void turnOffLed(int led) {
  digitalWrite(led, HIGH);
}
