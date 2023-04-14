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
        if (DEBUG) Serial.println("Iniciando modo #2");
        //initSmartphone();
        //initOkGoogle();
      }
      else
      {
        // Futuramente Home Assistant e Node Red
      }

      // Starting discovery UDP service
      //beginUDP();
    }
    else
    {
      desligarModoSTA();
    }
  }
}

void loop()
{
  if (getModoAP()) {
    dnsServer.processNextRequest();
    handleWebServer();
  }
  if (!getModoAP()) {
    if (getModoOperacao() == 1)
      alexaHandle();
    else if (getModoOperacao() == 2)
      handleOkGoogle();
    //handleUDP();
  }
}
