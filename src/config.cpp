#include "esp8266_iot.h"
#include "config.h"


bool readConfig(String path, String key, char* value)
{
  File configFile = LittleFS.open(path, "r");
  
  if (!configFile)
    return false; 
  

  String json = configFile.readString();
  JSONVar jo = JSON.parse(json);
  configFile.close();

  if (JSON.typeof(jo) == "undefined")
  {
    return false;
  }

  if (!jo.hasOwnProperty(key))
  {
    Serial.printf("Failed to read config key:%s", key.c_str());
    return false;
  }
    
  
  strcpy(value, jo[key]);
  return true;
}


bool writeConfig(String path, String key, String value)
{

  JSONVar jo;

  File configFile;

  if (LittleFS.exists(path))
  {
    configFile = LittleFS.open(path, "r+");
    String json = configFile.readString();
    jo = JSON.parse(json);
  }
  else
  {
    configFile = LittleFS.open(path, "w+");
  }
  

  
  jo[key] = value;
  configFile.seek(0);
  String json = JSON.stringify(jo);
  configFile.write(json.c_str());
  configFile.close();
  return true;
}


bool getJson(String path, char* buf)
{
  File configFile = LittleFS.open(path, "r");
  
  if (!configFile)
    return false;
  
  strcpy(buf, configFile.readString().c_str());
  configFile.close();
  return true;
}