void handleWebServer()
{
    server.handleClient();
}

void initWebServerModoRuntime()
{
    server.begin();
    if (DEBUG)
        Serial.println("Servidor Web no modo Runtime iniciado!");

    server.on("/", handleAcionamentoManual);
    server.on("/relay", handleRelay);
    server.onNotFound(handleFileSystem);
}

void handleAcionamentoManual()
{
    server.sendHeader("Location", String("/manual.html"), true);
    server.send(302, "text/plain", "");
}

void handleRelay()
{
    const char *status = server.arg(0).c_str();
    if ((strcmp(status, "1") == 0))
    {
        turnOffRelay();
    }
    else
    {
        turnOnRelay();
    }
    server.send(200, "text/plain", "");
}

String responseHTML = ""
                      "<!DOCTYPE html><html lang='en'><head>"
                      "<meta name='viewport' content='width=device-width'>"
                      "<title>CaptivePortal</title></head><body>"
                      "<h1>Hello World!</h1><p>This is a captive portal example."
                      " All requests will be redirected here.</p></body></html>";

void initWebServerModoConfig()
{
    server.begin();
    if (DEBUG)
        Serial.println("Servidor Web no modo AP iniciado!");

    server.on("/", handleIndex);
    server.on("/dispositivo", handleDevice);
    server.on("/dispositivo/state", handleDeviceState);
    server.on("/dominio", handleDomain);
    server.on("/dominio/state", handleDomainState);
    server.on("/modo", handleModoOperacao);
    server.on("/modo/state", handleModoOperacaoState);
    server.on("/wifi/config", handleWifiConfig);
    server.on("/wifi/state", handleWifiState);

    server.on("/mqtt/server/config", handleMQTTServerConfig);
    server.on("/mqtt/server/state", handleMQTTServerState);
    server.on("/mqtt/port/config", handleMQTTPortConfig);
    server.on("/mqtt/port/state", handleMQTTPortState);
    server.on("/mqtt/username/config", handleMQTTUsernameConfig);
    server.on("/mqtt/username/state", handleMQTTUsernameState);
    server.on("/mqtt/password/config", handleMQTTPasswordConfig);
    server.on("/mqtt/password/state", handleMQTTPasswordState);
    server.on("/mqtt/feed/config", handleMQTTFeedConfig);
    server.on("/mqtt/feed/state", handleMQTTFeedState);
    
    
    server.on("/relay", handleRelay);
    server.on("/reset", handleReset);
    server.onNotFound(handleFileSystem);
    //server.onNotFound([]() {
    //  server.send(200, "text/html", responseHTML);
    //});
}


void handleMQTTServerConfig () {}
void handleMQTTServerState () {}
void handleMQTTPortConfig () {}
void handleMQTTPortState () {}
void handleMQTTUsernameConfig () {}
void handleMQTTUsernameState () {}
void handleMQTTPasswordConfig () {}
void handleMQTTPasswordState () {}
void handleMQTTFeedConfig () {}
void handleMQTTFeedState () {}

void handleIndex()
{
    server.sendHeader("Location", String("/index.html"), true);
    server.send(302, "text/plain", "");
}

void handleDevice()
{
  if (DEBUG) Serial.print("Handle Device: ");
  if (DEBUG) Serial.println(server.arg(0).c_str());
    saveDevice(server.arg(0).c_str());
    handleDeviceState();
}

void handleDeviceState()
{
  if (DEBUG) Serial.print("Handle Device State: ");
  if (DEBUG) Serial.println(getDispositivo());
    server.send(200, "text/plain", getDispositivo());
}

void handleDomain()
{
    saveDomain(server.arg(0).c_str());
    handleDomainState();
}

void handleDomainState()
{
    server.send(200, "text/plain", getDominio());
}

void handleModoOperacao()
{
    const char *_retstr = server.arg(0).c_str();

    if (DEBUG) Serial.print("Handle Modo: ");
    if (DEBUG) Serial.println(server.arg(0).c_str());
    
    byte _ret;
    if (_retstr[0] == '1')
    {
        _ret = 1;
    }
    else
    {
        _ret = 2;
    }
    saveModoOperacao(_ret);
    handleModoOperacaoState();
}

void handleModoOperacaoState()
{
    byte _ret = getModoOperacao();
    if (_ret == 1)
        server.send(200, "text/plain", "1");
    else if (_ret == 2)
        server.send(200, "text/plain", "2");
    else
        server.send(200, "text/plain", "0");
}

void handleWifiConfig()
{
  if (DEBUG) Serial.print("Handle Wifi Config: ");
  if (DEBUG) Serial.print(server.arg(0).c_str());
  if (DEBUG) Serial.print("|");
  if (DEBUG) Serial.print(server.arg(1).c_str());
  if (DEBUG) Serial.println();
    saveWifiConfig(server.arg(0).c_str(), server.arg(1).c_str());
    handleWifiState();
}

void handleWifiState()
{
    char buf[41];
    const char *first = getWifiSsid();
    const char *second = getWifiPassword();
    strcpy(buf, first);
    strcat(buf, "|");
    strcat(buf, second);

    if (DEBUG) Serial.print("Handle Wifi State: ");
    if (DEBUG) Serial.println(buf);
    server.send(200, "text/plain", buf);
}

void handleReset()
{
    desligarModoAP();
    delay(100);
    ESP.restart();
}

void handleFileSystem()
{
    String path = ESP8266WebServer::urlDecode(server.uri());
    String contentType = mime::getContentType(path);
    if (DEBUG) {
      Serial.print(server.hostHeader());
      Serial.println(path);
      Serial.println(contentType);
    }
    if (!pathExists(path))
    {
        if (DEBUG) {
          Serial.println("redirecting to index");
        }
        path = "/index.html";
        contentType = "text/html";
    }

    if (pathExists(path))
    {
        if (DEBUG) {
          Serial.print("path exists: ");
          Serial.println(path);
        }
        File file = openFile(path);
        if (!file) {
            if (DEBUG) Serial.print("Erro ao abrir arquivo: ");
            if (DEBUG) Serial.println(path);
            server.send(200, "text/plain", "Erro ao abrir arquivo!");
        }
        else
            server.streamFile(file, contentType);
        closeFile(file);
    }
}
