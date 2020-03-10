#include "esp8266_iot.h"
#include "http_server.h"
#include "html.h"

const unsigned int http_port = 80;
ESP8266WebServer server(http_port);





void handleRoot()
{



  if (bNeedInit)
  {
    Serial.println("init");
    handleInit();
  }
  else
  {
    Serial.println("index");
    server.send(200, "text/html", indexPage);
  }

  
}


void handleInit()
{
  server.send(200, "text/html", initPage);
}


void handlePlain()
{
  if (server.method() != HTTP_POST)
  {
    server.send(405, "text/plain", "Method Not Allowed");
  }
  else
  {
    server.send(200, "text/plain", "POST body was:\n" + server.arg("plain"));
  }
}


void handleForm()
{
  if (server.method() != HTTP_POST)
  {
    server.send(405, "text/plain", "Method Not Allowed");
  }
  else
  {

    if (!server.hasArg("method"))
      server.send(405, "text/plain", "Method Not Allowed");

    String message = "POST form was:\n";
    const String method =  server.arg("method");

    if (method == "scan_wifi")
    {
      WifiData* wdata;
      int n = scanWIFI(wdata);
      
      if (!wdata)
      {
        server.send(200, "application/json", "{\"code\":1,\"msg\":\"No wifi detected!\"}");
        return;
      }
    
      DynamicJsonDocument doc(512);
      doc["code"] = 0;
      doc["msg"] = "Scan completed!";
      JsonArray data = doc.createNestedArray("data");

      for(int i = 0; i < n; i++)
      {
        JsonObject jo = data.createNestedObject();
        jo["ssid"] = (wdata + i)->ssid;
        jo["rssi"] = (wdata + i)->rssi;
        jo["encrypt"] = (wdata + i)->encrypt;
      }
      
      String json;
      serializeJson(doc, json);
      server.send(200, "application/json", json.c_str());
      delete[] wdata;
    }
    else if (method == "init_config")
    {
      if (!server.hasArg("wifi_ssid") || !server.hasArg("wifi_password"))
        server.send(405, "text/plain", "Method Not Allowed");

      const String wifi_ssid =  server.arg("wifi_ssid");
      const String wifi_password =  server.arg("wifi_password");
      char* json = new char[128];
      sprintf(json, "{wifi_ssid:\"%s\", wifi_password:\"%s\"}", wifi_ssid.c_str(), wifi_password.c_str());
      

      if (!writeConfig("/config.json", json))
      {
        
        server.send(200, "application/json", "{\"code\":1,\"msg\":\"write config error!\"}");
        return;
      }

      server.send(200, "application/json", "{\"code\":0,\"msg\":\"Config saved, system will be restart!\"}");
      delay(1000);
      ESP.restart();
    }
    else if (method == "reboot")
    {
      server.send(200, "application/json", "{\"code\":0,\"msg\":\"systemwill be restart!\"}");
      delay(1000);
      ESP.restart();
    }
    else if (method == "reset")
    {
      LittleFS.format();
      server.send(200, "application/json", "{\"code\":0,\"msg\":\"Format completed, system will be restart!\"}");
      delay(1000);
      ESP.restart();
    }


    for (uint8_t i = 0; i < server.args(); i++)
    {
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(200, "text/plain", message);
  }
}

void handleNotFound() 
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(LED_BUILTIN, 1);
}

void http_loop()
{
  server.handleClient();
}
