
struct UserConfig
{
  int id;
  char ssid[20];
  char password[20];
  char dispositivo[20];
  bool modoAP;
  byte modoOperacao;
};

int UserId = 91285;
int eeAddress = 0;
static struct UserConfig userConfig;

void initUserConfig()
{
  EEPROM.begin(512);
}

void SaveUserConfig(char *_ssid, char *_password, char *_dispositivo)
{
  userConfig.id = UserId;
  strcpy(userConfig.ssid, _ssid);
  strcpy(userConfig.password, _password);
  strcpy(userConfig.dispositivo, _dispositivo);
  userConfig.modoAP = false;
  EEPROM.put(eeAddress, userConfig);
  EEPROM.commit();
}

void SaveModoAP()
{
  userConfig.modoAP = true;
  EEPROM.put(eeAddress, userConfig);
  EEPROM.commit();
}

void TurnOffModoAP()
{
  userConfig.modoAP = false;
  EEPROM.put(eeAddress, userConfig);
  EEPROM.commit();
}

void SaveWifiConfig(const char *_ssid, const char *_pass)
{
  GetUserConfig();
  strcpy(userConfig.ssid, _ssid);
  strcpy(userConfig.password, _pass);
  EEPROM.put(eeAddress, userConfig);
  EEPROM.commit();
}

void SaveDevice(const char *_device)
{
  GetUserConfig();
  strcpy(userConfig.dispositivo, _device);
  EEPROM.put(eeAddress, userConfig);
  EEPROM.commit();
}

char *GetWifiSsid()
{
  return userConfig.ssid;
}

char *GetWifiPassword()
{
  return userConfig.password;
}

char *GetDispositivo()
{
  return userConfig.dispositivo;
}

void GetUserConfig()
{
  EEPROM.get(eeAddress, userConfig);
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

bool isUserConfigModeAP()
{
  return userConfig.modoAP;
}

void ClearUserConfig()
{
  for (int i = 0; i < 512; i++)
  {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
}

void configUser()
{
  initUserConfig();
  GetUserConfig();
  if (userConfig.id != UserId)
  {
    ClearUserConfig();
    SaveUserConfig("", "", "", 0);
    ResetDevice();
  }
}

bool CheckUserConfig()
{
  return strlen(userConfig.ssid) != 0 && strlen(userConfig.password) != 0 &&
         ((strlen(userConfig.dispositivo) != 0 && userConfig.modoOperacao == 1) ||
          (userConfig.modoOperacao != 2));
}
