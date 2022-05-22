static unsigned long contaTempo = 0;
static int contaVezes = 0;
const int limiteVezes = 7;
const int intervaloTempo = 300;

void configButton() {
  pinMode(BUTTON, INPUT_PULLUP);
  contaTempo = millis();
}

bool checkButton() 
{
  if (contaVezes >= limiteVezes) {
    contaVezes = 0;
    contaTempo = millis();
    return true;
  }
  if (!digitalRead(BUTTON) && contaTempo < millis()) {
    atualizaTempo();
    contaVezes++;
  }
  else if (digitalRead(BUTTON) && contaTempo > millis()) {
    contaVezes = 0;
    atualizaTempo();
  } 
  return false;
}

void atualizaTempo() {
  contaTempo = millis() + intervaloTempo;
}
