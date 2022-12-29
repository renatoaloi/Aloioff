void initEEPROM()
{
    EEPROM.begin(EEPROM_SIZE);
}

bool commitEEPROM(int address)
{
    EEPROM.put(address, userConfig);
    return EEPROM.commit();
}

void getEEPROM(int address)
{
    EEPROM.get(address, userConfig);
}

void clearEEPROM()
{
    for (int i = 0; i < EEPROM_SIZE; i++)
    {
        EEPROM.write(i, 0);
    }
    EEPROM.commit();
    delay(150);
}