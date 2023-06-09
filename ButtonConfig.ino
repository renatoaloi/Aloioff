static unsigned long contaTempo = 0;
static int contaVezes = 0;
const int limiteVezes = 7;
const int intervaloTempo = 300;
static bool buttonPressed = false;

void resetDevice() {
  ESP.restart();
}

void configButton() {
  pinMode(BUTTON, INPUT);
  digitalWrite(BUTTON, HIGH);
  contaTempo = millis();
}

bool checkButton() 
{
  if (contaVezes >= limiteVezes) {
    buttonPressed = false;
    contaVezes = 0;
    contaTempo = millis();
    return true;
  }
  if (!digitalRead(BUTTON) && contaTempo < millis()) {
    buttonPressed = true;
    atualizaTempo();
    contaVezes++;
  }
  else if (digitalRead(BUTTON) && contaTempo > millis()) {
    contaVezes = 0;
    atualizaTempo();
  }

  if (digitalRead(BUTTON) && buttonPressed) {
    buttonPressed = false;
    contaVezes = 0;
    contaTempo = millis();
    if (relayStatus) {
      turnOffRelay();
    } 
    else {
      turnOnRelay();
    }
  }
   
  return false;
}

void atualizaTempo() {
  contaTempo = millis() + intervaloTempo;
}
