void initSmartphone()
{
    server.on("/sp", handleSmartphone);
}

void smartphoneHandle()
{
    server.handleClient();
}

void handleSmartphone()
{
    server.send(200, "text/plain", "Teste de smartphone");
}