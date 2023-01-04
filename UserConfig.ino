void initUserConfig()
{
    initEEPROM();
    delay(150);
    getUserConfig();
    if (userConfig.id != UserId)
    {
        clearEEPROM();
        saveUserConfig("", "", "", 0, true);
    }
}

void saveUserConfig(const char *_ssid, const char *_password, const char *_dispositivo, byte _modo, bool _modoAP)
{
    userConfig.id = UserId;
    strcpy(userConfig.ssid, _ssid);
    strcpy(userConfig.password, _password);
    strcpy(userConfig.dispositivo, _dispositivo);
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
        userConfig.modoOperacao,
        _modo);
}

void saveWifiConfig(const char *_ssid, const char *_pass)
{
    saveUserConfig(
        _ssid,
        _pass,
        userConfig.dispositivo,
        userConfig.modoOperacao,
        userConfig.modoAP);
}

void saveDevice(const char *_device)
{
    saveUserConfig(
        userConfig.ssid,
        userConfig.password,
        _device,
        userConfig.modoOperacao,
        userConfig.modoAP);
}

void saveModoOperacao(byte _modo)
{
    saveUserConfig(
        userConfig.ssid,
        userConfig.password,
        userConfig.dispositivo,
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

byte getModoOperacao()
{
    return userConfig.modoOperacao;
}

bool getModoAP()
{
    return userConfig.modoAP;
}

void getUserConfig()
{
    getEEPROM(eeAddress);
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
        Serial.print("Modo AP ");
        Serial.println(userConfig.modoAP ? "ligado!" : "desligado!");
        Serial.print("Modo de Operacao ");
        Serial.println(userConfig.modoOperacao == 1 ? "Alexa" : userConfig.modoOperacao == 2 ? "Smartphone"
                                                                                             : "Nao implementado");
    }
}