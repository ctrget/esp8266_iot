#include "esp8266_iot.h"
#include "config.h"


bool readConfig(char* path, char* section, char* value)
{
  Serial.printf("ln %s \r", section);
  File configFile = LittleFS.open(path, "r");

  if (!configFile)
  {
    Serial.println("Failed to open config file");
    return false;
  }

  size_t size = configFile.size();

  if (size <= 0 || size > 1024)
  {
    Serial.println("Config file size is too large");
    configFile.close();
    return false;
  }



  
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, configFile);

  if (error)
  {
    Serial.println("Failed to read file, using default configuration");
    configFile.close();
    return false;
  }

  if (strlen(doc[section]) <= 0)
  {
    Serial.printf("cannot find section %s \r", section);
    configFile.close();
    return false;
  }

  strcpy(value, doc[section]);
  configFile.close();
  return true;
}


bool writeConfig(char* path, char* js)
{

  File configFile = LittleFS.open(path, "w+");

  if (!configFile)
  {
    Serial.println("Failed to create config file for writing");
    return false;
  }

    
  size_t size = configFile.size();

  if (size > 1024)
  {
    Serial.println("Config file size is too large");
    configFile.close();
    return false;
  }

  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, js);
  
  if (error)
  {
    Serial.printf(("error to write config %s \r"), js);
    configFile.close();
    return false;
  }

  if (serializeJson(doc, configFile) == 0) 
  {
    Serial.println(F("Failed to write to file"));
  }


  configFile.close();
  return true;
}
