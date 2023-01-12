void handleWebServer()
{
    if (getModoAP() || getModoOperacao() == 2)
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
    server.on("/relay", handleRelay);
    server.on("/reset", handleReset);
    server.onNotFound(handleFileSystem);
}

void handleIndex()
{
    server.sendHeader("Location", String("/index.html"), true);
    server.send(302, "text/plain", "");
}

void handleDevice()
{
    saveDevice(server.arg(0).c_str());
    handleDeviceState();
}

void handleDeviceState()
{
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
    if (path.endsWith("/"))
    {
        path += "index.html";
    }
    if (pathExists(path))
    {
        tempoOpenedFile = millis() + 5000;
        while (openedFile && millis() < tempoOpenedFile)
        {
            delay(10);
        };
        if (millis() > tempoOpenedFile)
        {
            server.send(500, "text/plain", "Tempo expirado tentando abrir arquivo!");
        }
        else
        {
            File file = openFile(path);
            server.streamFile(file, contentType);
            closeFile(file);
        }
    }
}