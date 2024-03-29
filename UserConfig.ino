void initUserConfig()
{
    initEEPROM();
    delay(150);
    getUserConfig();
    if (userConfig.id != UserId)
    {
        clearEEPROM();
        saveUserConfig("", "", "", "", 0, true, "", 0, "", "", "", "", "", "", "", "");
    }
}

void saveUserConfig(
  const char *_ssid, 
  const char *_password, 
  const char *_dispositivo, 
  const char *_dominio, 
  byte _modo, 
  bool _modoAP,
  const char *_mqttServer,
  int _mqttPort,
  const char *_mqttUsername,
  const char *_mqttPassword,
  const char *_mqttFeed,
  const char *_mqttCmd,
  const char *_mqttStatus,
  const char *_mqttDeviceClass,
  const char *_mqttPayloadOn,
  const char *_mqttPayloadOff
)
{
    userConfig.id = UserId;
    strcpy(userConfig.ssid, _ssid);
    strcpy(userConfig.password, _password);
    strcpy(userConfig.dispositivo, _dispositivo);
    strcpy(userConfig.dominio, _dominio);
    strcpy(userConfig.mqttServer, _mqttServer);
    userConfig.mqttPort = _mqttPort;
    strcpy(userConfig.mqttUsername, _mqttUsername);
    strcpy(userConfig.mqttPassword, _mqttPassword);
    strcpy(userConfig.mqttFeed, _mqttFeed);
    strcpy(userConfig.mqttCmd, _mqttCmd);
    strcpy(userConfig.mqttStatus, _mqttStatus);
    strcpy(userConfig.mqttDeviceClass, _mqttDeviceClass);
    strcpy(userConfig.mqttPayloadOn, _mqttPayloadOn);
    strcpy(userConfig.mqttPayloadOff, _mqttPayloadOff);
    userConfig.modoOperacao = _modo;
    userConfig.modoAP = _modoAP;
    commitEEPROM(eeAddress);
}

void saveMQTTServer(const char *_mqttServer)
{
    saveUserConfig(
        userConfig.ssid,
        userConfig.password,
        userConfig.dispositivo,
        userConfig.dominio,
        userConfig.modoOperacao,
        userConfig.modoAP,
        _mqttServer,
        userConfig.mqttPort,
        userConfig.mqttUsername,
        userConfig.mqttPassword,
        userConfig.mqttFeed,
        userConfig.mqttCmd,
        userConfig.mqttStatus,
        userConfig.mqttDeviceClass,
        userConfig.mqttPayloadOn,
        userConfig.mqttPayloadOff
    );
}

void saveMQTTPort(int _mqttPort)
{
    saveUserConfig(
        userConfig.ssid,
        userConfig.password,
        userConfig.dispositivo,
        userConfig.dominio,
        userConfig.modoOperacao,
        userConfig.modoAP,
        userConfig.mqttServer,
        _mqttPort,
        userConfig.mqttUsername,
        userConfig.mqttPassword,
        userConfig.mqttFeed,
        userConfig.mqttCmd,
        userConfig.mqttStatus,
        userConfig.mqttDeviceClass,
        userConfig.mqttPayloadOn,
        userConfig.mqttPayloadOff
    );
}

void saveMQTTUsername(const char *_mqttUsername)
{
    saveUserConfig(
        userConfig.ssid,
        userConfig.password,
        userConfig.dispositivo,
        userConfig.dominio,
        userConfig.modoOperacao,
        userConfig.modoAP,
        userConfig.mqttServer,
        userConfig.mqttPort,
        _mqttUsername,
        userConfig.mqttPassword,
        userConfig.mqttFeed,
        userConfig.mqttCmd,
        userConfig.mqttStatus,
        userConfig.mqttDeviceClass,
        userConfig.mqttPayloadOn,
        userConfig.mqttPayloadOff
    );
}

void saveMQTTPassword(const char *_mqttPassword)
{
    saveUserConfig(
        userConfig.ssid,
        userConfig.password,
        userConfig.dispositivo,
        userConfig.dominio,
        userConfig.modoOperacao,
        userConfig.modoAP,
        userConfig.mqttServer,
        userConfig.mqttPort,
        userConfig.mqttUsername,
        _mqttPassword,
        userConfig.mqttFeed,
        userConfig.mqttCmd,
        userConfig.mqttStatus,
        userConfig.mqttDeviceClass,
        userConfig.mqttPayloadOn,
        userConfig.mqttPayloadOff
    );
}

void saveMQTTFeed(const char *_mqttFeed)
{
    saveUserConfig(
        userConfig.ssid,
        userConfig.password,
        userConfig.dispositivo,
        userConfig.dominio,
        userConfig.modoOperacao,
        userConfig.modoAP,
        userConfig.mqttServer,
        userConfig.mqttPort,
        userConfig.mqttUsername,
        userConfig.mqttPassword,
        _mqttFeed,
        userConfig.mqttCmd,
        userConfig.mqttStatus,
        userConfig.mqttDeviceClass,
        userConfig.mqttPayloadOn,
        userConfig.mqttPayloadOff
    );
}

void saveModoAP(bool _modo)
{
    saveUserConfig(
        userConfig.ssid,
        userConfig.password,
        userConfig.dispositivo,
        userConfig.dominio,
        userConfig.modoOperacao,
        _modo,
        userConfig.mqttServer,
        userConfig.mqttPort,
        userConfig.mqttUsername,
        userConfig.mqttPassword,
        userConfig.mqttFeed,
        userConfig.mqttCmd,
        userConfig.mqttStatus,
        userConfig.mqttDeviceClass,
        userConfig.mqttPayloadOn,
        userConfig.mqttPayloadOff
    );
}

void saveWifiConfig(const char *_ssid, const char *_pass)
{
    saveUserConfig(
        _ssid,
        _pass,
        userConfig.dispositivo,
        userConfig.dominio,
        userConfig.modoOperacao,
        userConfig.modoAP,
        userConfig.mqttServer,
        userConfig.mqttPort,
        userConfig.mqttUsername,
        userConfig.mqttPassword,
        userConfig.mqttFeed,
        userConfig.mqttCmd,
        userConfig.mqttStatus,
        userConfig.mqttDeviceClass,
        userConfig.mqttPayloadOn,
        userConfig.mqttPayloadOff
    );
}

void saveDevice(const char *_device)
{
    saveUserConfig(
        userConfig.ssid,
        userConfig.password,
        _device,
        userConfig.dominio,
        userConfig.modoOperacao,
        userConfig.modoAP,
        userConfig.mqttServer,
        userConfig.mqttPort,
        userConfig.mqttUsername,
        userConfig.mqttPassword,
        userConfig.mqttFeed,
        userConfig.mqttCmd,
        userConfig.mqttStatus,
        userConfig.mqttDeviceClass,
        userConfig.mqttPayloadOn,
        userConfig.mqttPayloadOff
    );
}

void saveDomain(const char *_domain)
{
    saveUserConfig(
        userConfig.ssid,
        userConfig.password,
        userConfig.dispositivo,
        _domain,
        userConfig.modoOperacao,
        userConfig.modoAP,
        userConfig.mqttServer,
        userConfig.mqttPort,
        userConfig.mqttUsername,
        userConfig.mqttPassword,
        userConfig.mqttFeed,
        userConfig.mqttCmd,
        userConfig.mqttStatus,
        userConfig.mqttDeviceClass,
        userConfig.mqttPayloadOn,
        userConfig.mqttPayloadOff
    );
}

void saveModoOperacao(byte _modo)
{
    saveUserConfig(
        userConfig.ssid,
        userConfig.password,
        userConfig.dispositivo,
        userConfig.dominio,
        _modo,
        userConfig.modoAP,
        userConfig.mqttServer,
        userConfig.mqttPort,
        userConfig.mqttUsername,
        userConfig.mqttPassword,
        userConfig.mqttFeed,
        userConfig.mqttCmd,
        userConfig.mqttStatus,
        userConfig.mqttDeviceClass,
        userConfig.mqttPayloadOn,
        userConfig.mqttPayloadOff
    );
}

void saveMQTTCmd(const char *_mqttCmd)
{
    saveUserConfig(
        userConfig.ssid,
        userConfig.password,
        userConfig.dispositivo,
        userConfig.dominio,
        userConfig.modoOperacao,
        userConfig.modoAP,
        userConfig.mqttServer,
        userConfig.mqttPort,
        userConfig.mqttUsername,
        userConfig.mqttPassword,
        userConfig.mqttFeed,
        _mqttCmd,
        userConfig.mqttStatus,
        userConfig.mqttDeviceClass,
        userConfig.mqttPayloadOn,
        userConfig.mqttPayloadOff
    );
}

void saveMQTTStatus(const char *_mqttStatus)
{
    saveUserConfig(
        userConfig.ssid,
        userConfig.password,
        userConfig.dispositivo,
        userConfig.dominio,
        userConfig.modoOperacao,
        userConfig.modoAP,
        userConfig.mqttServer,
        userConfig.mqttPort,
        userConfig.mqttUsername,
        userConfig.mqttPassword,
        userConfig.mqttFeed,
        userConfig.mqttCmd,
        _mqttStatus,
        userConfig.mqttDeviceClass,
        userConfig.mqttPayloadOn,
        userConfig.mqttPayloadOff
    );
}

void saveMQTTDeviceClass(const char *_mqttDeviceClass)
{
    saveUserConfig(
        userConfig.ssid,
        userConfig.password,
        userConfig.dispositivo,
        userConfig.dominio,
        userConfig.modoOperacao,
        userConfig.modoAP,
        userConfig.mqttServer,
        userConfig.mqttPort,
        userConfig.mqttUsername,
        userConfig.mqttPassword,
        userConfig.mqttFeed,
        userConfig.mqttCmd,
        userConfig.mqttStatus,
        _mqttDeviceClass,
        userConfig.mqttPayloadOn,
        userConfig.mqttPayloadOff
    );
}

void saveMQTTPayloadOn(const char *_mqttPayloadOn)
{
    saveUserConfig(
        userConfig.ssid,
        userConfig.password,
        userConfig.dispositivo,
        userConfig.dominio,
        userConfig.modoOperacao,
        userConfig.modoAP,
        userConfig.mqttServer,
        userConfig.mqttPort,
        userConfig.mqttUsername,
        userConfig.mqttPassword,
        userConfig.mqttFeed,
        userConfig.mqttCmd,
        userConfig.mqttStatus,
        userConfig.mqttDeviceClass,
        _mqttPayloadOn,
        userConfig.mqttPayloadOff
    );
}

void saveMQTTPayloadOff(const char *_mqttPayloadOff)
{
    saveUserConfig(
        userConfig.ssid,
        userConfig.password,
        userConfig.dispositivo,
        userConfig.dominio,
        userConfig.modoOperacao,
        userConfig.modoAP,
        userConfig.mqttServer,
        userConfig.mqttPort,
        userConfig.mqttUsername,
        userConfig.mqttPassword,
        userConfig.mqttFeed,
        userConfig.mqttCmd,
        userConfig.mqttStatus,
        userConfig.mqttDeviceClass,
        userConfig.mqttPayloadOn,
        _mqttPayloadOff
    );
}

const char *getMQTTServer()
{
    return userConfig.mqttServer;
}

int getMQTTPort()
{
    return userConfig.mqttPort;
}

const char *getMQTTUsername()
{
    return userConfig.mqttUsername;
}

const char *getMQTTPassword()
{
    return userConfig.mqttPassword;
}

const char *getMQTTFeed()
{
    return userConfig.mqttFeed;
}

const char *getMQTTCmd()
{
    return userConfig.mqttCmd;
}

const char *getMQTTStatus()
{
    return userConfig.mqttStatus;
}

const char *getMQTTDeviceClass()
{
    return userConfig.mqttDeviceClass;
}

const char *getMQTTPayloadOn()
{
    return userConfig.mqttPayloadOn;
}

const char *getMQTTPayloadOff()
{
    return userConfig.mqttPayloadOff;
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
        Serial.println(
          userConfig.modoOperacao == 1 ? "Alexa" 
          : userConfig.modoOperacao == 2 ? "Google Home (Ok Google)"
          : userConfig.modoOperacao == 3 ? "Home Assistant (MQTT)"
          : userConfig.modoOperacao == 4 ? "Node Red (MQTT)"
          : "Desconhecido"
        );
        Serial.print("MQTT Server: ");
        Serial.println(userConfig.mqttServer);
        Serial.print("MQTT Port: ");
        Serial.println(userConfig.mqttPort);
        Serial.print("MQTT Username: ");
        Serial.println(userConfig.mqttUsername);
        Serial.print("MQTT Password: ");
        Serial.println(userConfig.mqttPassword);
        Serial.print("MQTT Feed: ");
        Serial.println(userConfig.mqttFeed);
        Serial.print("MQTT Cmd: ");
        Serial.println(userConfig.mqttCmd);
        Serial.print("MQTT Status: ");
        Serial.println(userConfig.mqttStatus);
        Serial.print("MQTT Device Class: ");
        Serial.println(userConfig.mqttDeviceClass);
        Serial.print("MQTT PayloadOn: ");
        Serial.println(userConfig.mqttPayloadOn);
        Serial.print("MQTT PayloadOff: ");
        Serial.println(userConfig.mqttPayloadOff);
    }
}
