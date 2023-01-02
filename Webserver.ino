void initWebServerModoAP()
{
    server.begin();
    if (DEBUG)
        Serial.println("Servidor iniciado!");

    server.on("/test", handleTest);
    server.on("/dispositivo", handleDevice);
    server.on("/dispositivo/state", handleDeviceState);
    server.on("/modo", handleModoOperacao);
    server.on("/modo/state", handleModoOperacaoState);
    server.on("/wifi/config", handleWifiConfig);
    server.on("/wifi/state", handleWifiState);
    server.on("/relay", handleRelay);
    server.on("/reset", handleReset);
    server.onNotFound(handleFileSystem);
}

void handleWebServer()
{
    if (getModoAP() || getModoOperacao() == 1)
        server.handleClient();
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

void handleTest() {}

void handleModoOperacao() {}
void handleModoOperacaoState() {}
void handleWifiConfig() {}
void handleWifiState() {}
void handleRelay() {}
void handleReset() {}

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