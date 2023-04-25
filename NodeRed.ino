void NodeRedCallback(char* topic, byte* payload, unsigned int length) {
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

void initNodeRed() {
  initRelay();
  mqttInit(NodeRedCallback);
  mqttConnect();
  mqttSubscribeTopic(getMQTTFeed());
}

void handleNodeRed() {
  mqttLoop();
}
