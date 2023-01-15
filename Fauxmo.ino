void initFauxmo()
{
    fauxmo.createServer(true);
    fauxmo.setPort(80);
    fauxmo.enable(true);
    // fauxmo.addDevice(getDispositivo());

    fauxmo.addDevice("iluminacao");

    fauxmo.onSetState(
        [](unsigned char device_id, const char *device_name, bool state, unsigned char value)
        {
            // if ((strcmp(device_name, getDispositivo()) == 0))
            if ((strcmp(device_name, "iluminacao") == 0))
            {
                if (state)
                {
                    turnOffRelay();
                }
                else
                {
                    turnOnRelay();
                }
            }
        });
}

void fauxmoHandle()
{
    fauxmo.handle();
}