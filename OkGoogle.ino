void MQTT_connect() {
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
  mqtt = Adafruit_MQTT_Client(
    &client, 
    getMQTTServer(), 
    getMQTTPort(), 
    getMQTTUsername(), 
    getMQTTPassword()
  );
  String strSubscribe = getMQTTUsername();
  strSubscribe.concat(getMQTTFeed());
  mqttFeed = Adafruit_MQTT_Subscribe(&mqtt, strSubscribe.c_str() );
  mqtt.subscribe(&mqttFeed);
  MQTT_connect();
}

void handleOkGoogle() {
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(20000))) {
    if (subscription == &mqttFeed) {
      Serial.print(F("Got: "));
      Serial.println((char *)mqttFeed.lastread);
      //int Light1_State = atoi((char *)mqttFeed.lastread);
      //digitalWrite(Relay1, !Light1_State);
    }
  }
}
