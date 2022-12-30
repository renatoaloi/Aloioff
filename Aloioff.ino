#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SPI.h>
#include <FS.h>
#include <LittleFS.h>
#include <EEPROM.h>
#include "fauxmoESP.h"

#ifndef APSSID
#define APSSID "ALOIOFF"
#define APPSK "12345678"
#endif

#define RELE 0
#define BUTTON 3
#define DEBUG 0
#define DEBUG_REMOTO 0
#define EEPROM_SIZE 128

const char *ssid = APSSID;
const char *password = APPSK;
const char *host = "aloioff";

IPAddress local_IP(10, 0, 0, 1);
IPAddress gateway(10, 0, 0, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80);

fauxmoESP fauxmo;

struct UserConfig
{
  int id;
  char ssid[20];
  char password[20];
  char dispositivo[20];
  bool modoAP;
  byte modoOperacao;
};

int UserId = 91286;
int eeAddress = 0;
static struct UserConfig userConfig;

static const char TEXT_PLAIN[] PROGMEM = "text/plain";

void setup()
{
  initUserConfig();

  if (getModoAP())
  {
    // Modo AP
    ligarWebServerModoAP();
  }
  else
  {
    // Modo de operacao STATION
    // depois que modo AP for configurado
    if (getModoOperacao() == 1)
    {
      // initAlexa();
    }
    else if (getModoOperacao() == 2)
    {
      // initSmartphone();
    }
    else
    {
      // Not implemented
    }
  }
}

void loop()
{
  handleWebServer();
}
