void ligarModoAP()
{
    initWifiModoAP();
    initFS();
    initWebServerModoConfig();
}

void desligarModoAP()
{
    saveModoAP(false);
    endFS();
}
