bool initFS()
{
    return LittleFS.begin();
}

bool pathExists(String path)
{
    return LittleFS.exists(path);
}

File openFile(String path)
{
    // openedFile = true;
    return LittleFS.open(path, "r");
}

void closeFile(File file)
{
    file.close();
    // openedFile = false;
}

void endFS()
{
    LittleFS.end();
}
