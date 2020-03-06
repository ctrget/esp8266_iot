#ifndef ESP8266_IOT
#define ESP8266_IOT

#include <Arduino.h>
#include <String.h>
#include <Wire.h>
#include <time.h>
#include <FS.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <U8g2lib.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "config.h"
#include "display.h"
#include "http_server.h"
#include "udp_server.h"

extern Display display;
extern bool bNeedInit;
extern bool bDisplay;

#endif
