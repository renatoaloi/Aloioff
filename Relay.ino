void initRelay()
{
    pinMode(RELE, OUTPUT);
    digitalWrite(RELE, LOW);
}

void turnOffRelay()
{
  if (DEBUG) Serial.println("turned Off Relay");
    digitalWrite(RELE, LOW);
}

void turnOnRelay()
{
  if (DEBUG) Serial.println("turned On Relay");
    digitalWrite(RELE, HIGH);
}
