#include "esp8266_iot.h"

unsigned long otime = 0;
void ICACHE_RAM_ATTR btn_click();
bool bNeedInit = true;
bool bDisplay = false;
Display display;

void btn_click()
{
  Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!click");
  
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


bool getLocalTime(struct tm * info, uint32_t ms)
{
  uint32_t count = ms / 10;
  time_t now;

  time(&now);
  localtime_r(&now, info);

  if (info->tm_year > (2016 - 1900))
  {
    return true;
  }

  while (count--)
  {
    delay(10);
    time(&now);
    localtime_r(&now, info);
    if (info->tm_year > (2016 - 1900))
    {
      return true;
    }
  }
  return false;
}




void initAP()
{
  WiFi.softAPConfig(IPAddress(192, 168, 1, 1), IPAddress(192, 168, 1, 1), IPAddress(255, 255, 255, 0));
  WiFi.softAP("8266", "12345678");
  IPAddress myIP = WiFi.softAPIP();
  Serial.println("AP IP address: ");
  Serial.println(myIP);
}


void setup(void) {
  Serial.begin(115200);
  pinMode(D5, INPUT);
  attachInterrupt(digitalPinToInterrupt(D5), btn_click, RISING);
  display.init();
  int timeout = 0;

  //led
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 1);



  Serial.println("Mount LittleFS");

  if (!LittleFS.begin())
  {
    Serial.println("LittleFS mount failed");
    return;
  }



  char wifi_ssid[32], wifi_password[16];
  bool bssid = readConfig("/config.json", "wifi_ssid", wifi_ssid);
  bool bpass = readConfig("/config.json", "wifi_password", wifi_password);
  bNeedInit = !(bssid && bpass);

  Serial.printf("ssid: %s pass: %s\r", wifi_ssid, wifi_password);


  if (bNeedInit)
  {
    initAP();
    Serial.println("Init AP mode!!!!!!!!!!!!!!");
  }
  else
  {
    Serial.println("Init STA mode!!!!!!!!!!!!!!");
    Serial.println(wifi_ssid);
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

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println(WiFi.localIP());
  }






  udp_server.begin(udp_port);
  server.on("/", handleRoot);
  server.on("/init", handleInit);
  server.on("/plain/", handlePlain);
  server.on("/form/", handleForm);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");


  long timezone = 8;
  byte daysavetime = 0;
  Serial.println("Contacting Time Server");
  configTime(3600 * timezone, daysavetime * 3600, "cn.ntp.org.cn", "0.pool.ntp.org", "1.pool.ntp.org");

  //struct tm tmstruct ;
  //(2000);
  //tmstruct.tm_year = 0;
  //getLocalTime(&tmstruct, 5000);
  //Serial.printf("\nNow is : %d-%02d-%02d %02d:%02d:%02d\n", (tmstruct.tm_year) + 1900, (tmstruct.tm_mon) + 1, tmstruct.tm_mday, tmstruct.tm_hour, tmstruct.tm_min, tmstruct.tm_sec);

}





void loop(void) {

  http_loop();
  udp_loop();
  delay(1);
}
