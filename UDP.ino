void beginUDP() {
  UDP.begin(UDP_PORT);
  if (DEBUG) Serial.print("Listening on UDP port: ");
  if (DEBUG) Serial.println(UDP_PORT);
}

void mountPacket() {
  UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
  String resposta = "";
  resposta.concat("{ \"ip\": \"");
  resposta.concat(WiFi.localIP().toString());
  resposta.concat("\", \"id\": ");
  resposta.concat(getUserConfigId());
  resposta.concat(", \"typeId\": ");
  resposta.concat(getModoOperacao());
  resposta.concat(", \"typeDescription\": \"");
  resposta.concat(getNameModoOperacao());
  resposta.concat("\", \"deviceName\": \"");
  resposta.concat(getDispositivo());
  resposta.concat("\" }");
  UDP.print(resposta);
  UDP.endPacket();
}

void handleUDP() {
  int packetSize = UDP.parsePacket();
  if (packetSize) {
    if (DEBUG) Serial.print("Received packet! Size: ");
    if (DEBUG) Serial.println(packetSize); 
    int len = UDP.read(packet, 255);
    if (len > 0)
    {
      packet[len] = '\0';
    }
    if (DEBUG) Serial.print("Received content! Msg: ");
    if (DEBUG) Serial.println(packet);
    if (strcmp(packet, "ESP-ACK") == 0) {
      if (DEBUG) Serial.println("Mounting packet...");
      mountPacket();
    }
    if (DEBUG) Serial.println("Finished responding UDP!");
  }
}
