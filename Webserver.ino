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

void initWebServerModoConfig()
{
    httpUpdater.setup(&server);
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
    server.on("/mqtt/config", handleMQTTConfig);
    server.on("/mqtt/state", handleMQTTState);
    server.on("/homeassistant/config", handleHomeAssistantConfig);
    server.on("/homeassistant/state", handleHomeAssistantState);
    server.on("/nodered/config", handleNodeRedConfig);
    server.on("/nodered/state", handleNodeRedState);
    server.on("/relay", handleRelay);
    server.on("/reset", handleReset);
    server.on("/update/firmware", handleFirmwareUpdate);
    server.on("/update/filesystem", handleFilesystemUpdate);
    server.onNotFound(handleFileSystem);
}

void handleFirmwareUpdate() {
  server.sendHeader("Location", String("/update/firmware.html"), true);
  server.send(302, "text/plain", "");
}

void handleFilesystemUpdate() {
  server.sendHeader("Location", String("/update/filesystem.html"), true);
  server.send(302, "text/plain", "");
}

void handleMQTTConfig () {
  const char *_feed = server.arg(0).c_str();
  const char *_server = server.arg(1).c_str();
  const char *_port = server.arg(2).c_str();
  const char *_username = server.arg(3).c_str();
  const char *_password = server.arg(4).c_str();

  saveMQTTFeed(_feed);
  saveMQTTServer(_server);
  saveMQTTPort(atoi(_port));
  saveMQTTUsername(_username);
  saveMQTTPassword(_password);
  
  handleDeviceState();
}


void handleMQTTState () {
  String mqttData = "";
  mqttData.concat(getMQTTFeed());
  mqttData.concat("|");
  mqttData.concat(getMQTTServer());
  mqttData.concat("|");
  mqttData.concat(getMQTTPort());
  mqttData.concat("|");
  mqttData.concat(getMQTTUsername());
  mqttData.concat("|");
  mqttData.concat(getMQTTPassword());
  if (DEBUG) Serial.print("Handle MQTT State: ");
  if (DEBUG) Serial.println(mqttData);
    server.send(200, "text/plain", mqttData.c_str());  
}

void handleHomeAssistantConfig () {
  const char *_feed = server.arg(0).c_str();
  const char *_cmd = server.arg(1).c_str();
  const char *_status = server.arg(2).c_str();
  const char *_deviceClass = server.arg(3).c_str();
  const char *_payloadOn = server.arg(4).c_str();
  const char *_payloadOff = server.arg(5).c_str();

  saveMQTTFeed(_feed);
  saveMQTTCmd(_cmd);
  saveMQTTStatus(_status);
  saveMQTTDeviceClass(_deviceClass);
  saveMQTTPayloadOn(_payloadOn);
  saveMQTTPayloadOff(_payloadOff);
  
  handleHomeAssistantState();
}


void handleHomeAssistantState () {
  String mqttData = "";
  mqttData.concat(getMQTTFeed());
  mqttData.concat("|");
  mqttData.concat(getMQTTCmd());
  mqttData.concat("|");
  mqttData.concat(getMQTTStatus());
  mqttData.concat("|");
  mqttData.concat(getMQTTDeviceClass());
  mqttData.concat("|");
  mqttData.concat(getMQTTPayloadOn());
  mqttData.concat("|");
  mqttData.concat(getMQTTPayloadOff());
  if (DEBUG) Serial.print("Handle HomeAssistant State: ");
  if (DEBUG) Serial.println(mqttData);
  server.send(200, "text/plain", mqttData.c_str());  
}

void handleNodeRedConfig () {
  const char *_feed = server.arg(0).c_str();
  const char *_payloadOn = server.arg(1).c_str();
  const char *_payloadOff = server.arg(2).c_str();

  saveMQTTFeed(_feed);
  saveMQTTPayloadOn(_payloadOn);
  saveMQTTPayloadOff(_payloadOff);
  
  handleNodeRedState();
}


void handleNodeRedState () {
  String mqttData = "";
  mqttData.concat(getMQTTFeed());
  mqttData.concat("|");
  mqttData.concat(getMQTTPayloadOn());
  mqttData.concat("|");
  mqttData.concat(getMQTTPayloadOff());
  if (DEBUG) Serial.print("Handle NodeRed State: ");
  if (DEBUG) Serial.println(mqttData);
  server.send(200, "text/plain", mqttData.c_str());  
}

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
    if (DEBUG) Serial.print("Handle Modo: ");
    if (DEBUG) Serial.println(server.arg(0).c_str());
    const char *_retstr = server.arg(0).c_str();
    byte _ret = _retstr[0] - '0';
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
