#include <ArduinoJson.h>
#include "FS.h"

bool config_load() {
  File configFile = SPIFFS.open("/config.js", "r");
  if (!configFile) {
    Serial.println("Failed to open config file");
    return false;
  }

  size_t size = configFile.size();
  if (size > 1024) {
    Serial.println("Config file size is too large");
    return false;
  }

  // Allocate a buffer to store contents of the file.
//  std::unique_ptr<char[]> buf(new char[size]);
  char buf[size];
  // We don't use String here because ArduinoJson library requires the input
  // buffer to be mutable. If you don't use ArduinoJson, you may as well
  // use configFile.readString instead.
  configFile.readBytes(buf, size);
  
  StaticJsonBuffer<750> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(&buf[16]);

  if (!json.success()) {
    Serial.println("Failed to parse config file");
    return false;
  } else {
    json.prettyPrintTo(Serial);
  }

//  const char* serverName = json["serverName"];
//  const char* accessToken = json["accessToken"];

  JsonArray& configArray = json["config"];

  for(int i=0; i< configArray.size();i++){
    modes[i].soundEnabled = configArray[i]["settings"][0];
    modes[i].ledsEnabled = configArray[i]["settings"][1];
  }
  Serial.println("Finished Loading Config");
  // Real world application would store these values in some variables for
  // later use.

  return true;
}

bool config_save() {
  StaticJsonBuffer<750> jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  JsonArray& configArray = json.createNestedArray("config");
  for(int i = 0; i<NUM_MODES;i++){
    JsonObject& configObj = configArray.createNestedObject();
    configObj["title"] = modes[i].title;
    JsonArray& settingsArray = configObj.createNestedArray("settings");
    settingsArray.add(modes[i].soundEnabled);
    settingsArray.add(modes[i].ledsEnabled);
  }
  
  File configFile = SPIFFS.open("/config.js", "w");
  if (!configFile) {
    Serial.println("Failed to open config file for writing");
    return false;
  }
  configFile.print("var configObj = ");
  
  json.printTo(configFile);
  return true;
}

