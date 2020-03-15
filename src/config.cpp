#include "esp8266_iot.h"
#include "config.h"


bool readConfig(String path, String key, char* value)
{
  DynamicJsonDocument doc(1024);
  File configFile = LittleFS.open(path, "r");
  
  if (!configFile)
  {
    /*
    String str;
    str = configFile.readString();
    Serial.printf("rad:%s\r", str.c_str());
    configFile.seek(0);
    */
   //DeserializationError error = deserializeJson(doc, configFile);
    return false; 
  }

  String json = configFile.readString();
  Serial.printf("json:%s", json.c_str());
  JSONVar jo = JSON.parse(json);
  configFile.close();

  if (JSON.typeof(jo) == "undefined")
  {
    return false;
  }

  if (JSON.typeof(jo[key]) == "undefined")
  {
    Serial.printf("Failed to read config key:%s", key.c_str());
    return false;
  }
    

  strcpy(value, jo[key]);
  return true;
}


bool writeConfig(String path, String key, String value)
{

  //DynamicJsonDocument doc(1024);
  JSONVar jo;

  File configFile;

  if (LittleFS.exists(path))
  {
    configFile = LittleFS.open(path, "r+");
    //deserializeJson(doc, configFile);
    String json = configFile.readString();
    jo = JSON.parse(json);
  }
  else
  {
    configFile = LittleFS.open(path, "w+");
  }
  

  
  jo[key] = value;
  configFile.seek(0);
  //serializeJson(doc, configFile);
  String json = JSON.stringify(jo);
  configFile.write(json.c_str());
  configFile.close();
  return true;
}