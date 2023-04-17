void HomeAssistantConnect() {
  mqttConnect();
}

void HomeAssistantCallback(char* topic, byte* payload, unsigned int length) {
  if (DEBUG) Serial.print("Message arrived [");
  if (DEBUG) Serial.print(topic);
  if (DEBUG) Serial.print("] ");
  for (int i = 0; i < length; i++) {
    if (DEBUG) Serial.print((char)payload[i]);
  }
  if (DEBUG) Serial.println();

  if ((char)payload[0] == '1') {
    turnOnRelay();
  } else {
    turnOffRelay();
  }

}

void initHomeAssistant() {
  initRelay();
  mqttInit(HomeAssistantCallback);
}

void handleHomeAssistant() {
  HomeAssistantConnect();
  mqttLoop();
}
