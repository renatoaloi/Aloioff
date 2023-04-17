#include "Aloioff.h"

void setup()
{
  if (DEBUG)
  {
    Serial.begin(115200);
    delay(500);
  }

  initUserConfig();
  configButton();

  if (getModoAP())
  {
    // Modo AP
    ligarModoAP();
  }
  else
  {
    // Modo de operacao STATION
    ligarModoSTA();

    if (!IsWiFiNotConnected())
    {
      // depois que modo STA for configurado
      if (getModoOperacao() == 1)
      {
        initAlexa();
      }
      else if (getModoOperacao() == 2)
      {
        if (DEBUG) Serial.println("Iniciando modo #2");
        initOkGoogle();
      }
      else if (getModoOperacao() == 3)
      {
        if (DEBUG) Serial.println("Iniciando modo #3");
        initHomeAssistant();
      }

      // Starting discovery UDP service
      beginUDP();
    }
    else
    {
      desligarModoSTA();
    }
  }
}

void loop()
{
  if (checkButton()) {
    saveUserConfig("", "", "", "", 0, true, "", 0, "", "", "", "", "", "", "", "");
    saveModoAP(true);
    resetDevice();
  }
  if (getModoAP()) {
    dnsServer.processNextRequest();
    handleWebServer();
  }
  if (!getModoAP()) {
    if (getModoOperacao() == 1)
      alexaHandle();
    else if (getModoOperacao() == 2)
      handleOkGoogle();
    else if (getModoOperacao() == 3)
      handleHomeAssistant();
    handleUDP();
  }
}
