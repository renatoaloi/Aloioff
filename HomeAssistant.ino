void HomeAssistantCallback(char* topic, byte* payload, unsigned int length) {
  if (DEBUG) Serial.print("Message arrived [");
  if (DEBUG) Serial.print(topic);
  if (DEBUG) Serial.print("] ");
  String msgArrived = "";
  for (int i = 0; i < length; i++) {
    msgArrived.concat((char)payload[i]);
  }
  if (DEBUG) Serial.println(msgArrived);
  if (msgArrived.equals(getMQTTPayloadOn())) {
    turnOnRelay();
  } else if (msgArrived.equals(getMQTTPayloadOff())) {
    turnOffRelay();
  }
}

void publishInitialStateTopic(const char *topicState, const char* topicInitalValue) {
  mqttPublishMessage(topicState, topicInitalValue);
}

void subscribeSwitchTopic(const char *topicCommand) {
  mqttSubscribeTopic(topicCommand);
}

void initHomeAssistant() {
  initRelay();
  mqttInit(HomeAssistantCallback);
  mqttConnect();
  createDeviceConfigTopic();
  subscribeSwitchTopic(getMQTTCmd());
  publishInitialStateTopic(getMQTTStatus(), getMQTTPayloadOff());
}

void handleHomeAssistant() {
  mqttLoop();
}

void publishConfigTopic(const char *topicConfig, String topicConfigJson) {
  Serial.println();
  Serial.println(topicConfig);
  Serial.println(topicConfigJson);
  Serial.println(topicConfigJson.c_str());
  mqttPublishRetainedMessage(topicConfig, topicConfigJson, 2000);
}

String createUniqueIdByMillis() {
  unsigned long currentMillis = millis();
  char text[UID_LEN + 1];
  for (int i = 0; i < UID_LEN; i++) {
    text[i] = 'A' + (currentMillis + i) % 26;
  }
  text[UID_LEN] = '\0';
  return String(text);
}

void createDeviceConfigTopic() {
  String topicConfigJson;
  topicConfigJson.reserve(2000);
  topicConfigJson = generateConfigJson(
    createUniqueIdByMillis().c_str(), 
    getMQTTDeviceClass(), 
    getDispositivo(), 
    getMQTTStatus(), 
    getMQTTCmd(),
    getMQTTPayloadOn(),
    getMQTTPayloadOff(),
    getMQTTPayloadOn(),
    getMQTTPayloadOff()
  );
  publishConfigTopic(getMQTTFeed(), topicConfigJson); 
}

String generateConfigJson(
  const char* unique_id, 
  const char* device_class, 
  const char* name, 
  const char* state_topic, 
  const char* command_topic,
  const char* payload_on,
  const char* payload_off,
  const char* state_on,
  const char* state_off
) {
  String payload = "{\"unique_id\": \"";
  payload.concat(unique_id);
  payload.concat("\", \"device_class\": \"");
  payload.concat(device_class);
  payload.concat("\", \"name\": \"");
  payload.concat(name);
  payload.concat("\", \"state_topic\": \"");
  payload.concat(state_topic);
  payload.concat("\", \"command_topic\": \"");
  payload.concat(command_topic);
  payload.concat("\", \"payload_on\": \"");
  payload.concat(payload_on);
  payload.concat("\", \"payload_off\": \"");
  payload.concat(payload_off);
  payload.concat("\", \"state_on\": \"");
  payload.concat(state_on);
  payload.concat("\", \"state_off\": \"");
  payload.concat(state_off);
  payload.concat("\" }");
  return payload;
}
