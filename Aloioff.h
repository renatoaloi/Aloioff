#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <SPI.h>
#include <FS.h>
#include <LittleFS.h>
#include <EEPROM.h>
#include "fauxmoESP.h"
#include <DNSServer.h>
#include <WiFiUdp.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define UDP_PORT 12345

#ifndef APSSID
#define APSSID "ALOIOFF"
#define APPSK ""
#endif

#define RELE 0
#define BUTTON 3
#define DEBUG 1
#define DEBUG_REMOTO 0
#define EEPROM_SIZE 512
#define WIFI_STA_TIMEOUT 10000

const byte DNS_PORT = 53;
const char *ssid = APSSID;
const char *password = APPSK;

IPAddress local_IP(10, 0, 0, 1);
IPAddress gateway(10, 0, 0, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80);
DNSServer dnsServer;
fauxmoESP fauxmo;
WiFiUDP UDP;

char packet[255];
char reply[] = "Packet received!";

struct UserConfig
{
  int  id;
  char ssid[20];
  char password[20];
  char dispositivo[20];
  char dominio[20];
  bool modoAP;
  byte modoOperacao;
  char mqttServer[20];
  int  mqttPort;
  char mqttUsername[20];
  char mqttPassword[40];
  char mqttFeed[40];
};

unsigned long tempoOpenedFile = 0L;
static bool openedFile = false;
int UserId = 91307;
int eeAddress = 0;
static struct UserConfig userConfig;

static const char TEXT_PLAIN[] PROGMEM = "text/plain";
