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
const char *host = "aloitech";

IPAddress local_IP(10, 0, 0, 1);
IPAddress gateway(10, 0, 0, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80);

fauxmoESP fauxmo;

static const char TEXT_PLAIN[] PROGMEM = "text/plain";

void setup()
{
  initSerial();
  configUser();
  initFileSystem();
  configButton();
  initWiFi();
  checkAndSelectSetupOperationMode();
}

void loop()
{
  checkButtonForResetAndCleanEeprom();
  checkAndSelectLoopOperationMode();
}
