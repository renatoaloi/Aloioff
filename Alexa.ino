void initAlexa() {
  pinMode(RELE, OUTPUT);
  digitalWrite(RELE, HIGH);
  fauxmo.createServer(true);
  fauxmo.setPort(80);
  fauxmo.enable(true);
  fauxmo.addDevice(GetDispositivo());

  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
    if ( (strcmp(device_name, GetDispositivo()) == 0) ) {
      if (state) {
        digitalWrite(RELE, LOW);
      } else {
        digitalWrite(RELE, HIGH);
      }
    }
  });
}

void alexaHandle() {
  fauxmo.handle();
}
