#include "esp8266_iot.h"

unsigned long otime = 0;
void ICACHE_RAM_ATTR btn_click();
struct tm localTime;
bool bNeedInit = true;
bool bDisplay = true;
Display display;
DNSServer dnsServer;
UdpServer udpServer;
const IPAddress apIP(192, 168, 1, 1);
const byte DNS_PORT = 53;
void btn_click()
{
  int gpio_d5 = digitalRead(D5);
  if (gpio_d5)
    bDisplay = !bDisplay;

  if (bDisplay)
  {
    display.showTest();
  }
  else
    display.clearDisplay();
}

void getNtpTime()
{
  long timezone = 8;
  byte daysavetime = 0;
  configTime(3600 * timezone, daysavetime * 3600, "ntp.ntsc.ac.cn", "ntp.aliyun.com", "time1.cloud.tencent.com");
}


bool getLocalTime()
{
  uint32_t count = 3000 / 10;
  time_t now;
  time(&now);
  localtime_r(&now, &localTime);
  if (localTime.tm_year > (2016 - 1900))
  {
    return true;
  }
  return false;
}

int scanWIFI(WifiData* wdata, int len)
{
  int n = WiFi.scanNetworks();
  if (n > 0)
  {
    len = n > len ? len : n; 

    for (int i = 0; i < len; i++)
    {
      wdata[i].ssid = WiFi.SSID(i);
      wdata[i].rssi = WiFi.RSSI(i);
      wdata[i].encrypt = WiFi.encryptionType(i);
    }
  }
  return n;
}

void initAP()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("ESP82266_Setup");
  display.printf("WIFI SSID: %s\r","8266_ Setup");
  display.printf("Config URL: %s\r","http://192.168.1.1");
  dnsServer.start(DNS_PORT, "*", apIP);
}

void setup(void) 
{
  pinMode(D5, INPUT);
  attachInterrupt(digitalPinToInterrupt(D5), btn_click, RISING);
  localTime.tm_year = 0;
  display.init();
  int timeout = 0;
  //led
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 1);
  display.printf("Mount LittleFS...");
  if (!LittleFS.begin())
  {
    display.printf("LittleFS mount failed!");
    return;
  }
  char wifi_ssid[32], wifi_password[16];
  bool bssid = readConfig("/config.json", "wifi_ssid", wifi_ssid);
  bool bpass = readConfig("/config.json", "wifi_password", wifi_password);
  bNeedInit = !(bssid && bpass);
  if (bNeedInit)
  {
    initAP();
    display.printf("Init AP mode...");
  }
  else
  {
    display.printf("Init STA mode...");
    display.printf("connecting to %s\r", wifi_ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(wifi_ssid, wifi_password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      if (timeout > 20)
      {
        WiFi.disconnect(false);
        initAP();
        break;
      }
      timeout++;
      Serial.print(".");
    }
    display.printf("WiFi connected!");
    display.printf("Local IP: %s", WiFi.localIP().toString().c_str());
  }

  udp_server.begin(udp_port);
  server.on("/", handleRoot);
  server.on("/init", handleInit);
  server.on("/api", handleAPI);
  server.on("/plain", handlePlain);
  server.on("/form", handleForm);
  server.onNotFound(handleNotFound);
  server.begin();
  display.printf("HTTP server started!");
  getNtpTime();
  display.clearDisplay();

}

void loop(void) 
{
  if (localTime.tm_year < (2016 - 1900) && !bNeedInit)
  {
    if (millis() - otime > 5000)
    {
      otime = millis();
      getNtpTime();
    }
  }
  display.loop();
  dnsServer.processNextRequest();
  http_loop();
  udpServer.udp_loop();
  delay(1);
}
