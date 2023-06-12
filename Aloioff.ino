#include "Aloioff.h"

void setup()
{
  if (DEBUG)
  {
    Serial.begin(115200);
    delay(500);
  }

  setupLeds();

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
      else if (getModoOperacao() == 4)
      {
        if (DEBUG) Serial.println("Iniciando modo #4");
        initNodeRed();
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
    blinkLed2Fast();
    blinkLed1Slow();
  }
  if (!getModoAP()) {
    if (getModoOperacao() == 1)
      alexaHandle();
    else if (getModoOperacao() == 2)
      handleOkGoogle();
    else if (getModoOperacao() == 3)
      handleHomeAssistant();
    else if (getModoOperacao() == 4)
      handleNodeRed();
    handleUDP();
  }
}
