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
#define APSSID "ALOITECH"
#define APPSK  "12345678"
#endif

#define RELE 0
#define BUTTON 3

#define DEBUG 0

const char *ssid = APSSID;
const char *password = APPSK;
const char *host = "aloitech";

IPAddress local_IP(10,0,0,1);
IPAddress gateway(10,0,0,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

fauxmoESP fauxmo;

static const char TEXT_PLAIN[] PROGMEM = "text/plain";

void setup() {
  if (DEBUG) Serial.begin(115200);
  delay(500);
  if (!initFS()) {
    if (DEBUG) Serial.println("Erro ao iniciar FS");
    while(1);
  }
  configUser();
  configButton();
  initWiFi();
  if (!isUserConfigModeAP() && CheckUserConfig()) {
    initAlexa();
  }
  else {
    server.begin();
    if (DEBUG) Serial.println("Servidor iniciado!");
  }
}

void loop() {
  if (checkButton()) {
    SaveUserConfig("", "", "");
    SaveModoAP();
    ResetDevice();
  }
  if (!isUserConfigModeAP() && CheckUserConfig()) {
    // terminou de configura modo ap
    alexaHandle();
  } else {
    server.handleClient();
  }
}
