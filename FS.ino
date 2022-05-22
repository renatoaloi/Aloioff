bool initFS() {
  return LittleFS.begin();
}

bool handleFileRead(String path) {
  Serial.println(String("handleFileRead: ") + path);

  if (path.endsWith("/")) {
    path += "index.html";
  }

  String contentType;
  if (server.hasArg("download")) {
    contentType = F("application/octet-stream");
  } else {
    contentType = mime::getContentType(path);
  }

  if (!LittleFS.exists(path)) {
    path = path + ".gz";
  }
  if (LittleFS.exists(path)) {
    File file = LittleFS.open(path, "r");
    if (server.streamFile(file, contentType) != file.size()) {
      Serial.println("Sent less data than expected!");
    }
    file.close();
    return true;
  }

  return false;
}
