#ifndef HTTP_SERVER
#define HTTP_SERVER

extern ESP8266WebServer server;

void http_loop();
void handleRoot();
void handleInit();
void handleAPI();
void handlePlain();
void handleForm();
void handleNotFound();



#endif
