void MQTT_connect(Adafruit_MQTT_Client mqtt) {
  int8_t ret;
  if (mqtt.connected()) return;
  if (DEBUG) Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) {
    if (DEBUG) Serial.println(mqtt.connectErrorString(ret));
    if (DEBUG) Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);
    retries--;
    if (retries == 0) break;
  }
  if (DEBUG) { 
    if (retries)
      Serial.println("MQTT Connected!");
    else 
      Serial.println("FAILED !!! MQTT NOT Connected!");
  }
}

void initOkGoogle() {
//  mqtt = Adafruit_MQTT_Client(
//    &client, 
//    getMQTTServer(), 
//    getMQTTPort(), 
//    getMQTTUsername(), 
//    getMQTTPassword()
//  );
//  char subsFeed[256];
//  strcpy(subsFeed, "");
//  sprintf(subsFeed, "%s%s", getMQTTUsername(), getMQTTFeed()); 
//  if (DEBUG) Serial.println(subsFeed);
//  mqttFeed = Adafruit_MQTT_Subscribe(&mqtt, subsFeed);
//  mqtt.subscribe(&mqttFeed);
//  MQTT_connect();
}

void handleOkGoogle() {
//  WiFiClient client;
//  static Adafruit_MQTT_Client mqtt = Adafruit_MQTT_Client(
//    &client, 
//    getMQTTServer(), 
//    getMQTTPort(), 
//    getMQTTUsername(), 
//    getMQTTPassword()
//  );
//  char subsFeed[256];
//  strcpy(subsFeed, "");
//  sprintf(subsFeed, "%s%s", getMQTTUsername(), getMQTTFeed()); 
//  if (DEBUG) Serial.println(subsFeed);
//  Adafruit_MQTT_Subscribe mqttFeed = Adafruit_MQTT_Subscribe(&mqtt, subsFeed);
//  mqtt.subscribe(&mqttFeed);
//  //
//  MQTT_connect(mqtt);
//  Adafruit_MQTT_Subscribe *subscription;
//  if ((subscription = mqtt.readSubscription(500))) {
//    if (DEBUG) Serial.print("Lendo subscricoes...");
//    if (subscription == &mqttFeed) {
//      if (DEBUG) Serial.print(F("Got: "));
//      if (DEBUG) Serial.println((char *)mqttFeed.lastread);
//    }
//    else {
//      if (DEBUG) Serial.print("Nenhuma subscricao!");
//      if (DEBUG) delay(100);
//    }
//  }
}
