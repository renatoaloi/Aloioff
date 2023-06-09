void initRelay()
{
    pinMode(RELE, OUTPUT);
    digitalWrite(RELE, LOW);
}

void turnOffRelay()
{
  relayStatus = false;
  if (DEBUG) Serial.println("turned Off Relay");
  turnOffLed(LED2);
  digitalWrite(RELE, LOW);
}

void turnOnRelay()
{
  relayStatus = true;
  if (DEBUG) Serial.println("turned On Relay");
  turnOnLed(LED2);
  digitalWrite(RELE, HIGH);
}
