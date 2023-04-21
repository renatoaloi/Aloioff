void mqttReconnect() {
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

void mqttConnect() {
  if (!mqtt.connected()) {
    mqttReconnect();
  }
}

void mqttInit(std::function<void(char*, uint8_t*, unsigned int)> callback) {
  mqtt.setServer(getMQTTServer(), getMQTTPort());
  mqtt.setCallback(callback);
}

void mqttPublishRetainedMessage(const char *topic, String message, unsigned long bufferSize) {
  mqtt.setBufferSize(bufferSize);
  mqtt.publish(topic, message.c_str(), true);
}

void mqttPublishMessage(const char *topic, String message) {
  mqtt.setBufferSize(256);
  mqtt.publish(topic, message.c_str());
}

void mqttSubscribeTopic(const char *topic) {
  mqtt.subscribe(topic);
}

void mqttLoop() {
  if (!mqtt.connected()) {
    mqttReconnect();
  }
  mqtt.loop();
}
