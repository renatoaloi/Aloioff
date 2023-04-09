#include "Aloioff.h"

void setup()
{
  if (DEBUG)
  {
    Serial.begin(115200);
    delay(500);
  }

  initUserConfig();

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
        initSmartphone();
      }
      else
      {
        // Futuramente OK Google
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
  if (getModoAP() || getModoOperacao() == 2) {
    if (getModoAP()) dnsServer.processNextRequest();
    handleWebServer();
  }
  if (!getModoAP()) {
    if (getModoOperacao() == 1)
      alexaHandle();
    handleUDP();
  }
}
