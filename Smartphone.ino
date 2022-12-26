void initSmartphone()
{
    configureRelayPortAndStartWebServer();
    server.on("/", handleAcionamentoManual);
    server.on("/teste", handleSmartphone);
    server.on("/relay", handleRelay);
    server.onNotFound(handleFileSystem);
}

void handleAcionamentoManual()
{
    server.sendHeader("Location", String("/manual.html"), true);
    server.send(302, "text/plain", "");
}

void smartphoneHandle()
{
    if (!IsWiFiNotConnected())
        server.handleClient();
    // else
    //     ConnectWiFiSTA();
}

void handleSmartphone()
{
    server.send(200, "text/plain", "Teste de smartphone");
}