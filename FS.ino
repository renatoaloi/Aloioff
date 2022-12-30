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
    return LittleFS.open(path, "r");
}

void closeFile(File file)
{
    file.close();
}
