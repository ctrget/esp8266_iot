#ifndef CONFIG_H
#define CONFIG_H


bool writeConfig(String path, String key, String value);
bool readConfig(String path, String key, char* value);
bool getJson(String path, char* buf);

#endif
