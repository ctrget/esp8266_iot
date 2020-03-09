#include "esp8266_iot.h"

unsigned long otime = 0;
void ICACHE_RAM_ATTR btn_click();
struct tm localTime;
bool bNeedInit = true;
bool bDisplay = true;
Display display;
UdpServer udpServer;


void btn_click()
{
  
  int gpio_d5 = digitalRead(D5);

  if (gpio_d5)
    bDisplay = !bDisplay;

  if (bDisplay)
  {
    display.showTest();
    //u8g2.clearBuffer();          // clear the internal memory
    //u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
    //u8g2.drawStr(0, 10, "Hello World!"); // write something to the internal memory
    //u8g2.sendBuffer();          // transfer internal memory to the display
  }
  else
    display.clearDisplay();
  //u8g2.clearDisplay();
  

}


void getNtpTime()
{
  long timezone = 8;
  byte daysavetime = 0;
  configTime(3600 * timezone, daysavetime * 3600, "ntp.ntsc.ac.cn", "ntp.aliyun.com", "time1.cloud.tencent.com");
}

int get_mem()
{
  uint32_t free;
  uint16_t max;
  uint8_t frag;
  ESP.getHeapStats(&free, &max, &frag);

  //Serial.printf("free: %5d - max: %5d - frag: %3d%% <- ", free, max, frag);
  // %s requires a malloc that could fail, using println instead:
  return free;
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

/*
  while (count--)
  {
    delay(10);
    time(&now);
    localtime_r(&now, &localTime);
    if (localTime.tm_year > (2016 - 1900))
    {
      return true;
    }
  }
  */
 
  return false;
}




void initAP()
{
  WiFi.softAPConfig(IPAddress(192, 168, 1, 1), IPAddress(192, 168, 1, 1), IPAddress(255, 255, 255, 0));
  WiFi.softAP("8266", "12345678");
  IPAddress myIP = WiFi.softAPIP();
  display.printf("AP IP address: %s", myIP.toString().c_str());
}


void setup(void) 
{

  Serial.begin(1500000);
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
    display.printf("connecting to %s...", wifi_ssid);
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
  server.on("/plain/", handlePlain);
  server.on("/form/", handleForm);
  server.onNotFound(handleNotFound);
  server.begin();
  display.printf("HTTP server started!");
  getNtpTime();
  display.clearDisplay();

}





void loop(void) 
{
  
  if (localTime.tm_year < (2016 - 1900))
  {
    
    if (millis() - otime > 5000)
    {
      otime = millis();
      getNtpTime();
    }

  }
  
  
  display.loop();
  http_loop();
  udpServer.udp_loop();
  delay(1);
}
