#include "esp8266_iot.h"
#include "config.h"


bool readConfig(String path, String key, char* value)
{
  DynamicJsonDocument doc(1024);
  File configFile = LittleFS.open(path, "r");
  
  if (configFile)
  {
    /*
    String str;
    str = configFile.readString();
    Serial.printf("rad:%s\r", str.c_str());
    configFile.seek(0);
    */
    DeserializationError error = deserializeJson(doc, configFile);
    configFile.close();

    if (error)
    {
      return false;
    }

  }
  else
  {
    return false;
  }


  if (!doc[key])
  {
    Serial.printf("Failed to read config key:%s", key.c_str());
    return false;
  }
    

  strcpy(value, doc[key]);
  return true;
}

bool writeConfig(String path, String key, String value)
{

  DynamicJsonDocument doc(1024);
  File configFile;

  if (LittleFS.exists(path))
  {
    configFile = LittleFS.open(path, "r+");
    deserializeJson(doc, configFile);
  }
  else
  {
    configFile = LittleFS.open(path, "w+");
  }
  

  
  doc[key] = value;
  configFile.seek(0);
  serializeJson(doc, configFile);
  configFile.close();
  return true;
}