#include "esp8266_iot.h"
#include "http_server.h"
#include "html.h"

const unsigned int http_port = 80;
ESP8266WebServer server(http_port);
void handleRoot()
{
  if (bNeedInit)
  {
    handleInit();
  }
  else
  {
    server.send(200, "text/html", indexPage);
  }
}
void handleInit()
{
  server.send(200, "text/html", initPage);
}
void handleAPI()
{
  if (server.hasArg("scan_wifi"))
  {
    WifiData* wdata = new WifiData[10];
    int n = scanWIFI(wdata, 10);
    if (n <= 0)
    {
      server.send(200, "application/json", "{\"code\":1,\"msg\":\"No wifi detected!\"}");
      return;
    }

    JSONVar jo;
    jo["code"] = 0;
    jo["msg"] = "Scan completed!";
    JSONVar ja;

    for(int i = 0; i < n; i++)
    {
      JSONVar ji;
      ji["ssid"] = (wdata + i)->ssid;
      ji["rssi"] = (wdata + i)->rssi;
      ji["encrypt"] = (wdata + i)->encrypt;
      ja[i] = ji;

    }

    jo["data"] = ja;
    String json;
    json = JSON.stringify(jo);
    server.send(200, "application/json", json.c_str());
    delete[] wdata;
  }
  else if (server.hasArg("get_config"))
  {
    char* buf = new char[512];
    if (!getJson("/config.json", buf))
    {
      server.send(200, "application/json", "{\"code\":1,\"msg\":\"get config error!\"}");
      return;
    }  

    JSONVar jo;
    JSONVar jd = JSON.parse(buf);
    jo["code"] = 0;
    jo["msg"] = "OK";
    jo["data"] = jd;
    server.send(200, "application/json", JSON.stringify(jo));
    delete[] buf;
  }
  else
    server.send(405, "text/html", "Method Not Allowed");
}
void handlePlain()
{
  if (server.method() != HTTP_POST)
  {
    server.send(405, "text/html", "Method Not Allowed");
  }
  else
  {
    server.send(200, "text/html", "POST body was:\n" + server.arg("plain"));
  }
}
void handleForm()
{
  if (server.method() != HTTP_POST)
  {
    server.send(405, "text/html", "Method Not Allowed");
  }
  else
  {
    if (!server.hasArg("method"))
      server.send(405, "text/html", "Method Not Allowed");
    const String method =  server.arg("method");
    if (method == "init_config")
    {
      if (!server.hasArg("wifi_ssid") || !server.hasArg("wifi_password"))
        server.send(405, "text/html", "Method Not Allowed");
      const String wifi_ssid =  server.arg("wifi_ssid");
      const String wifi_password =  server.arg("wifi_password");

      if (!(writeConfig("/config.json", "wifi_ssid", wifi_ssid) && writeConfig("/config.json", "wifi_password", wifi_password)))
      {
        server.send(200, "application/json", "{\"code\":1,\"msg\":\"write config error!\"}");
        return;
      }
      
      server.send(200, "application/json", "{\"code\":0,\"msg\":\"Config saved, system will be restart!\"}");
      delay(1000);
      ESP.restart();
    }
    else if (method == "save_config")
    {
      if (!server.hasArg("wifi_ssid") || !server.hasArg("wifi_password") || !server.hasArg("weather_appid") || !server.hasArg("weather_appsecret"))
        server.send(405, "text/html", "Method Not Allowed");

      const String wifi_ssid =  server.arg("wifi_ssid");
      const String wifi_password =  server.arg("wifi_password");
      const String weather_appid = server.arg("weather_appid");
      const String weather_appsecret = server.arg("weather_appsecret");

      if (!(writeConfig("/config.json", "wifi_ssid", wifi_ssid) && writeConfig("/config.json", "wifi_password", wifi_password) && writeConfig("/config.json", "weather_appid", weather_appid) && writeConfig("/config.json", "weather_appsecret", weather_appsecret)))
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
    else
    {
      server.send(405, "text/html", "Method Not Allowed");
    }
  }
}
void handleNotFound() 
{
  if (bNeedInit)
  {
    handleInit();
    return;
  }
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/html", message);
}
void http_loop()
{
  server.handleClient();
}
