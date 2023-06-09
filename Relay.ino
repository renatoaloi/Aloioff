void initRelay()
{
    pinMode(RELE, OUTPUT);
    digitalWrite(RELE, LOW);
}

void turnOffRelay()
{
  relayStatus = false;
  if (DEBUG) Serial.println("turned Off Relay");
  digitalWrite(LED2, HIGH);
  digitalWrite(RELE, LOW);
}

void turnOnRelay()
{
  relayStatus = true;
  if (DEBUG) Serial.println("turned On Relay");
  digitalWrite(LED2, LOW);
  digitalWrite(RELE, HIGH);
}
