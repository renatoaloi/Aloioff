void resetBlink() {
  blinkRate = millis();
}

void setupLeds() {
  resetBlink();
  blinkStatus = false;
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, HIGH);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED2, HIGH);
}

void blinkLed2Fast() {
  blinkLeds(LED2, 300);
}

void blinkLed1Slow() {
  blinkLeds(LED1, 2000);
}

void blinkLeds(int led, int rate) {
  if (blinkRate + rate < millis()) {
    if (blinkStatus) {
      blinkStatus = false;
      digitalWrite(led, HIGH);
    }
    else {
      blinkStatus = true;
      digitalWrite(led, LOW);
    }
    resetBlink();
  }
}

void turnOnLed(int led) {
  digitalWrite(led, LOW);
}

void turnOffLed(int led) {
  digitalWrite(led, HIGH);
}
