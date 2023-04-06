#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SPI.h>
#include <FS.h>
#include <LittleFS.h>
#include <EEPROM.h>
#include "fauxmoESP.h"
#include <DNSServer.h>

#ifndef APSSID
#define APSSID "ALOIOFF"
#define APPSK ""
#endif

#define RELE 0
#define BUTTON 3
#define DEBUG 1
#define DEBUG_REMOTO 0
#define EEPROM_SIZE 128
#define WIFI_STA_TIMEOUT 10000

const byte DNS_PORT = 53;
const char *ssid = APSSID;
const char *password = APPSK;
const char *host = "aloioff";

IPAddress local_IP(10, 0, 0, 1);
IPAddress gateway(10, 0, 0, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80);
DNSServer dnsServer;
fauxmoESP fauxmo;

struct UserConfig
{
  int id;
  char ssid[20];
  char password[20];
  char dispositivo[20];
  char dominio[20];
  bool modoAP;
  byte modoOperacao;
};

unsigned long tempoOpenedFile = 0L;
static bool openedFile = false;
int UserId = 91300;
int eeAddress = 0;
static struct UserConfig userConfig;

static const char TEXT_PLAIN[] PROGMEM = "text/plain";

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
  if (!getModoAP() && getModoOperacao() == 1)
    alexaHandle();
}
