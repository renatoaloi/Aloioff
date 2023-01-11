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
    if (DEBUG)
        Serial.print("STA Connection established!");
}

void initWifiModoSTA()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(getWifiSsid(), getWifiPassword());
    WaitForConnection();
    MDNS.begin(getDominio());
}