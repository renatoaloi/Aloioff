void initFauxmo()
{
    fauxmo.createServer(true);
    fauxmo.setPort(80);
    fauxmo.enable(true);
    fauxmo.addDevice(getDispositivo());
    fauxmo.onSetState(
        [](unsigned char device_id, 
        const char *device_name, 
        bool state, 
        unsigned char value)
        {
            if ((strcmp(device_name, getDispositivo()) == 0))
            {
                if (state)
                {
                    turnOnRelay();
                }
                else
                {
                    turnOffRelay();
                }
            }
        });
}

void fauxmoHandle()
{
    fauxmo.handle();
}
