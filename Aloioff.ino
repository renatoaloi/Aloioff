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
  Serial.begin(115200);
  initFS();
  configUser();
  configButton();
  initWiFi();
  if (!isUserConfigModeAP() && CheckUserConfig()) {
    initAlexa();
  }
  else {
    server.begin();
  }
}

void loop() {
  if (checkButton()) {
    SaveUserConfig("", "", "");
    SaveModoAP();
//    pinMode(RELE, OUTPUT);
//    for (int i = 0; i < 10; i++) {
//      digitalWrite(RELE, 1);
//      delay(500);
//      digitalWrite(RELE, 0);
//      delay(500);
//    }
    ResetDevice();
  }
  if (!isUserConfigModeAP() && CheckUserConfig()) {
    // terminou de configura modo ap
    alexaHandle();
  } else {
    server.handleClient();
  }
}
