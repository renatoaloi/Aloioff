void initWiFi() 
{
  if (isUserConfigModeAP()) {
    // modo ap
    if (DEBUG) Serial.print("Setting soft-AP configuration ... ");
    bool isSuccess = WiFi.softAPConfig(local_IP, gateway, subnet);
    if (DEBUG) {
      Serial.println(isSuccess ? "Ready" : "Failed!");
      Serial.println("Configuring access point...");
    }
    WiFi.softAP(ssid, password);
    IPAddress myIP = WiFi.softAPIP();
    if (DEBUG) {
      Serial.print("AP IP address: ");
      Serial.println(myIP);
    }

    server.on("/test", handleTest);
    server.on("/dispositivo", handleDevice);
    server.on("/dispositivo/state", handleDispositivoState);
    server.on("/wifi/config", handleWifiConfig);
    server.on("/wifi/state", handleWifiState);
    server.on("/reset", handleReset);
    server.onNotFound(handleFileSystem);
  }
  else {
    // terminou de configura modo ap
    ////////////////////////////////
    // WI-FI INIT
    if (DEBUG) Serial.printf("Connecting to %s\n", GetWifiSsid());
    WiFi.mode(WIFI_STA);
    WiFi.begin(GetWifiSsid(), GetWifiPassword());
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      if (DEBUG) Serial.print(".");
      if (checkButton()) {
        SaveUserConfig("", "", "");
        SaveModoAP();
        ResetDevice();
      }
    }
    if (DEBUG)  {
      Serial.println("");
      Serial.print(F("Connected! IP address: "));
      Serial.println(WiFi.localIP());
    }
  }
}

void handleTest() {
  server.send(200, "text/plain", "Teste de rede");
}

void handleReset() {
  TurnOffModoAP();
  ResetDevice();
}

void handleWifiState() {
  char buf[41];
  const char *first = GetWifiSsid();
  const char *second = GetWifiPassword();
  strcpy(buf,first);
  strcat(buf, "|");
  strcat(buf,second);
  server.send(200, "text/plain", buf);
}

void handleDispositivoState() {
  server.send(200, "text/plain", GetDispositivo());
}

void handleDevice() {
  SaveDevice(server.arg(0).c_str());
  //server.send(200, "text/html", "<h1>Dispositivo: " + server.arg(0) + "</h1>");
  server.sendHeader("Location", String("/config.html"), true);
  server.send(302, "text/plain", "");
}

void handleWifiConfig() {
  if (DEBUG) {
    Serial.print("SSID: ");
    Serial.println(server.arg(0).c_str());
    Serial.print("PASS: ");
    Serial.println(server.arg(1).c_str());
  }
  SaveWifiConfig(server.arg(0).c_str(), server.arg(1).c_str());
  //server.send(200, "text/html", "<h1>Wifi ssid: " + server.arg(0) + ", Wifi pass: " + server.arg(1) + "</h1>");
  server.sendHeader("Location", String("/wifi.html"), true);
  server.send(302, "text/plain", "");
}

void replyNotFound(String msg) {
  server.send(404, FPSTR(TEXT_PLAIN), msg);
}

void handleFileSystem() {
  String uri = ESP8266WebServer::urlDecode(server.uri());
  if (handleFileRead(uri)) {
    return;
  }
  String message;
  message.reserve(100);
  message = F("Error: File not found\n\nURI: ");
  message += uri;
  message += F("\nMethod: ");
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += F("\nArguments: ");
  message += server.args();
  message += '\n';
  for (uint8_t i = 0; i < server.args(); i++) {
    message += F(" NAME:");
    message += server.argName(i);
    message += F("\n VALUE:");
    message += server.arg(i);
    message += '\n';
  }
  message += "path=";
  message += server.arg("path");
  message += '\n';
  if (DEBUG) Serial.print(message);
  return replyNotFound(message);
}
