void initWifiModoAP()
{
    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP(ssid, password);
    IPAddress myIP = WiFi.softAPIP();
    if (DEBUG)
    {
        Serial.print("AP IP address: ");
        Serial.println(myIP);
    }
}

bool IsWiFiNotConnected()
{
    return WiFi.status() != WL_CONNECTED;
}

void WaitForConnection()
{
    unsigned long timeout = millis() + WIFI_STA_TIMEOUT;
    while (IsWiFiNotConnected() && millis() < timeout)
    {
        delay(100);
    }
    if (DEBUG) {
        if (IsWiFiNotConnected()) {
            Serial.println("Erro ao conectar no WiFi!");
        }
        else {
            Serial.println("STA Connection established!");
            Serial.println("");
            Serial.print("Connected to ");
            Serial.println(getWifiSsid());
            Serial.print("IP address: ");
            Serial.println(WiFi.localIP());
        }
    }
}

void initWifiModoSTA()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(getWifiSsid(), getWifiPassword());
    WaitForConnection();
    if (!IsWiFiNotConnected()) {
        bool isMDNSOk = MDNS.begin(getDominio());
        if (DEBUG) {
            if (!isMDNSOk) Serial.println("Erro ao iniciar DNS!");
            else Serial.println("DNS iniciado com sucesso!");
        }
    }
    
}