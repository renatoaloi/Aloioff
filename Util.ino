void initSerial()
{
  if (DEBUG || DEBUG_REMOTO)
    Serial.begin(115200);
  delay(500);
}

void initFileSystem()
{
  if (!initFS())
  {
    if (DEBUG)
      Serial.println("Erro ao iniciar FS");
    while (1)
      ;
  }
}

void configureRelayPortAndStartWebServer()
{
  pinMode(RELE, OUTPUT);
  digitalWrite(RELE, LOW);
  server.begin();
  if (DEBUG)
    Serial.println("Servidor iniciado!");
}

void checkAndSelectSetupOperationMode()
{
  if (DEBUG)
  {
    Serial.print("Checkuserconfig: ");
    Serial.println(CheckUserConfig() ? "true" : "false");
  }
  if (!isUserConfigModeAP() && CheckUserConfig())
  {
    byte modoOperacao = GetModoOperacao();
    if (modoOperacao == 1)
    {
      if (DEBUG)
        Serial.println("Modo de operacao ALEXA!");
      initAlexa();
    }
    else if (modoOperacao == 2)
    {
      if (DEBUG)
        Serial.println("Modo de operacao SMARTPHONE!");
      initSmartphone();
    }
    else
    {
      if (DEBUG)
        Serial.println("Modo de operacao invalido!");
    }
  }
  else
  {
    configureRelayPortAndStartWebServer();
  }
}

void checkButtonForResetAndCleanEeprom()
{
  if (checkButton())
  {
    SaveUserConfig("", "", "", 0);
    SaveModoAP();
    ResetDevice();
  }
}

void checkAndSelectLoopOperationMode()
{
  if (!isUserConfigModeAP() && CheckUserConfig())
  {
    // terminou de configura modo ap
    byte modoOperacao = GetModoOperacao();
    if (modoOperacao == 1)
    {
      alexaHandle();
    }
    else if (modoOperacao == 2)
    {
      smartphoneHandle();
    }
    else
    {
      if (DEBUG)
        Serial.println("Handle invalido!");
      return;
    }
  }
  else
  {
    server.handleClient();
  }
}

void ResetDevice()
{
  ESP.restart();
}
