void initRelay()
{
    pinMode(RELE, OUTPUT);
    digitalWrite(RELE, LOW);
}

void turnOffRelay()
{
    digitalWrite(RELE, LOW);
}

void turnOnRelay()
{
    digitalWrite(RELE, HIGH);
}