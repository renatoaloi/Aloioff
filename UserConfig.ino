void initUserConfig()
{
    initEEPROM();
    delay(150);
    getUserConfig();
    if (userConfig.id != UserId)
    {
        clearEEPROM();
        saveUserConfig("", "", "", "", 0, true);
    }
}

void saveUserConfig(const char *_ssid, const char *_password, const char *_dispositivo, const char *_dominio, byte _modo, bool _modoAP)
{
    userConfig.id = UserId;
    strcpy(userConfig.ssid, _ssid);
    strcpy(userConfig.password, _password);
    strcpy(userConfig.dispositivo, _dispositivo);
    strcpy(userConfig.dominio, _dominio);
    userConfig.modoOperacao = _modo;
    userConfig.modoAP = _modoAP;
    commitEEPROM(eeAddress);
}

void saveModoAP(bool _modo)
{
    saveUserConfig(
        userConfig.ssid,
        userConfig.password,
        userConfig.dispositivo,
        userConfig.dominio,
        userConfig.modoOperacao,
        _modo);
}

void saveWifiConfig(const char *_ssid, const char *_pass)
{
    saveUserConfig(
        _ssid,
        _pass,
        userConfig.dispositivo,
        userConfig.dominio,
        userConfig.modoOperacao,
        userConfig.modoAP);
}

void saveDevice(const char *_device)
{
    saveUserConfig(
        userConfig.ssid,
        userConfig.password,
        _device,
        userConfig.dominio,
        userConfig.modoOperacao,
        userConfig.modoAP);
}

void saveDomain(const char *_domain)
{
    saveUserConfig(
        userConfig.ssid,
        userConfig.password,
        userConfig.dispositivo,
        _domain,
        userConfig.modoOperacao,
        userConfig.modoAP);
}

void saveModoOperacao(byte _modo)
{
    saveUserConfig(
        userConfig.ssid,
        userConfig.password,
        userConfig.dispositivo,
        userConfig.dominio,
        _modo,
        userConfig.modoAP);
}

const char *getWifiSsid()
{
    return userConfig.ssid;
}

const char *getWifiPassword()
{
    return userConfig.password;
}

const char *getDispositivo()
{
    return userConfig.dispositivo;
}

const char *getDominio()
{
    return userConfig.dominio;
}

byte getModoOperacao()
{
    return userConfig.modoOperacao;
}

const char* getNameModoOperacao()
{
    if (userConfig.modoOperacao == 1)
    {
      return "Echo Dot (Alexa)";
    }
    else if (userConfig.modoOperacao == 2)
    {
      return "Google Home (Ok Google)";
    }
    else if (userConfig.modoOperacao == 3)
    {
      return "Home Assistant (MQTT)";
    }
    else if (userConfig.modoOperacao == 4)
    {
      return "Node Red (MQTT)";
    }
    return "Desconhecido";
}

bool getModoAP()
{
    return userConfig.modoAP;
}

int getUserConfigId() {
  return userConfig.id;
}

void getUserConfig()
{
    if (DEBUG) Serial.println("Carregando configuracoes de usuario...");
    getEEPROM(eeAddress);
    if (DEBUG) Serial.println("Configuracoes de usuario carregadas com sucesso!");
    if (DEBUG)
    {
        Serial.print("id: ");
        Serial.println(userConfig.id);
        Serial.print("ssid: ");
        Serial.println(userConfig.ssid);
        Serial.print("password: ");
        Serial.println(userConfig.password);
        Serial.print("dispositivo: ");
        Serial.println(userConfig.dispositivo);
        Serial.print("dominio: ");
        Serial.println(userConfig.dominio);
        Serial.print("Modo AP ");
        Serial.println(userConfig.modoAP ? "ligado!" : "desligado!");
        Serial.print("Modo de Operacao ");
        Serial.println(userConfig.modoOperacao == 1 ? "Alexa" : userConfig.modoOperacao == 2 ? "Smartphone"
                                                                                             : "Nao implementado");
    }
}
