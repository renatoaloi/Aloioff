void MQTT_reconnect() {
  while (!mqtt.connected()) {
    if (DEBUG) Serial.print("Attempting MQTT connection...");
    String clientId = "Aloioff-" + String(getUserConfigId());
    if (mqtt.connect(clientId.c_str(), getMQTTUsername(), getMQTTPassword())) {
      if (DEBUG) Serial.println("connected");
      String subsFeed = String(getMQTTUsername()) + String(getMQTTFeed());
      mqtt.subscribe(subsFeed.c_str());
    } else {
      if (DEBUG) Serial.print("failed, rc=");
      if (DEBUG) Serial.print(mqtt.state());
      if (DEBUG) Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void OkGoogleConnect() {
  if (!mqtt.connected()) {
    MQTT_reconnect();
  }
}

void OkGoogleCallback(char* topic, byte* payload, unsigned int length) {
  if (DEBUG) Serial.print("Message arrived [");
  if (DEBUG) Serial.print(topic);
  if (DEBUG) Serial.print("] ");
  for (int i = 0; i < length; i++) {
    if (DEBUG) Serial.print((char)payload[i]);
  }
  if (DEBUG) Serial.println();

  if ((char)payload[0] == '1') {
    
  } else {
    
  }

}

void initOkGoogle() {
  mqtt.setServer(getMQTTServer(), getMQTTPort());
  mqtt.setCallback(OkGoogleCallback);
}

void handleOkGoogle() {
  OkGoogleConnect();
  mqtt.loop();
}
