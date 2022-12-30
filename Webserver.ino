void initWebServerModoAP()
{
    server.on("/test", handleTest);
    server.on("/dispositivo", handleDevice);
    server.on("/dispositivo/state", handleDispositivoState);
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

void handleTest() {}
void handleDevice() {}
void handleDispositivoState() {}
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
        File file = openFile(path);
        server.streamFile(file, contentType) != file.size();
        closeFile(file);
    }
}