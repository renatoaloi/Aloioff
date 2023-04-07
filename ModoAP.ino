void ligarModoAP()
{
    initWifiModoAP();
    if (initFS()) {
      if (DEBUG) Serial.println("FS iniciado com sucesso!");
    }
    else {
      if (DEBUG) Serial.println("Erro ao iniciar FS!");
    }
    initWebServerModoConfig();
}

void desligarModoAP()
{
    saveModoAP(false);
    endFS();
}
