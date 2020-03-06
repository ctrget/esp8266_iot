#ifndef HTTP_SERVER
#define HTTP_SERVER

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

extern ESP8266WebServer server;

void http_loop();
void handleRoot();
void handleInit();
void handlePlain();
void handleForm();
void handleNotFound();



#endif
