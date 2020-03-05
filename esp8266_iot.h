#ifndef ESP8266_IOT
#define ESP8266_IOT

#include <Arduino.h>
#include <String.h>
#include <Wire.h>
#include <time.h>
#include <FS.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include "config.h"
#include "display.h"
#include "http_server.h"
#include "udp_server.h"

extern Display display;
extern bool bNeedInit;
extern bool bDisplay;

#endif
