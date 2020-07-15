#include "esp8266_iot.h"
#include <Stepper.h>

// 设置步进电机旋转一圈是多少步
#define STEPS_PER_ROTOR_REV 32
const int GEAR_REDUCTION = 64;
const float STEPS_PER_OUT_REV = STEPS_PER_ROTOR_REV * GEAR_REDUCTION;

Stepper stepper(STEPS_PER_ROTOR_REV, digitalPinToInterrupt(D5), digitalPinToInterrupt(D7), digitalPinToInterrupt(D6), digitalPinToInterrupt(D8));

unsigned long otime = 0;
struct tm localTime;
bool bNeedInit = true;
bool bNeedUpdate = false;
IPAddress updateAddr;
int tDisplay = 0;
Display display;
DNSServer dnsServer;
UdpServer udpServer;

const byte firmwareVer = 0x1;
const IPAddress apIP(192, 168, 1, 1);
const byte DNS_PORT = 53;
//PCF8563 rtc;

void ICACHE_RAM_ATTR btn_click()
{
  /*
  int gpio_d5 = digitalRead(D5);
  if (gpio_d5)
    bDisplay = !bDisplay;

  if (bDisplay)
  {
    //display.showTest();
  }
  else
    display.clearDisplay();
    */

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
  if (localTime.tm_year > (2019 - 1900))
  {
    //DateTime now = DateTime(localTime.tm_year, localTime.tm_mon, localTime.tm_mday, localTime.tm_hour, localTime.tm_min, localTime.tm_sec);
    //rtc.adjust(now);
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
  return len;
}

void initAP()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("ESP82266_Setup");
  display.printf("WIFI SSID: %s\r","8266_ Setup");
  display.printf("Config URL: %s\r","http://192.168.1.1");
  bool b = dnsServer.start(DNS_PORT, "*", apIP);
}

void update_started()
{
  Serial.println("CALLBACK:  HTTP update process started");
}

void update_finished()
{
  Serial.println("CALLBACK:  HTTP update process finished");
}

void update_progress(int cur, int total)
{
  int progress = round((float)cur / total * 100);
  display.drawProgress(progress, "正在升级,请勿断电!");
}

void update_error(int err)
{
  Serial.printf("CALLBACK:  HTTP update fatal error code %d\n", err);
}

void setup(void) 
{
  Serial.begin(115200);
  //pinMode(D5, INPUT);
  //attachInterrupt(digitalPinToInterrupt(D5), btn_click, RISING);
  localTime.tm_year = 0;
  display.init();
  int timeout = 0;


  //led
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  display.printf("Mount LittleFS..............................................................................................................");

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
    display.printf("Connecting To");
    display.printf(wifi_ssid);
    WiFi.mode(WIFI_STA);
    WiFi.setAutoReconnect(true);
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
  display.ready();
  /*
  pinMode(D3, INPUT);
  attachInterrupt(digitalPinToInterrupt(D3), alarm, FALLING);
  rtc.begin();

  if (!rtc.isrunning()) 
  {
    Serial.println("RTC is NOT running!");
  }
  else
  {
    setAlarm(1);
  }
  */
  

  /*
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  digitalWrite(D5, HIGH);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, HIGH);
*/


}

void setAlarm(int value)
{

  /*
  char buf[100];
  strncpy(buf, "DD.MM.YYYY hh:mm:ss\0", 100);

  DateTime alarm = rtc.now();
  alarm.setminute( alarm.minute() + value);
  Serial.print("Setting alarm: ");
  strncpy(buf, "DD hh:mm MM\0", 100);
  Serial.println(alarm.format(buf));
  rtc.set_alarm( alarm, {AE_M, 0,  0, 0});
  rtc.on_alarm();
  */
}

void ICACHE_RAM_ATTR alarm()
{
  Serial.println("WakeUp atmega");
}


void setColor(int red, int green, int blue)
{
  analogWrite(D5, (255-red) * 4);
  analogWrite(D6, (255-green) * 4);
  analogWrite(D7, (255-blue) * 4);  
}

void setStepper(int mode)
{
  int StepsRequired = STEPS_PER_OUT_REV / 2;
  stepper.setSpeed(800);

  while(StepsRequired > 0)
  {
    int step = mode == 0 ? 1 : -1;
    stepper.step(step);
    delay(1);
    StepsRequired--;
  }  

}

void loop(void) 
{


  /*
  setColor(255, 52, 179);  // 黄色
  delay(1000);  



    DateTime now = rtc.now();
    char buf[100];
    strncpy(buf, "DD.MM.YYYY hh:mm:ss\0", 100);
    Serial.println(now.format(buf));

    delay(1000);
  
  */



  while(bNeedUpdate)
  {
    ESPhttpUpdate.setLedPin(LED_BUILTIN, LOW);
    ESPhttpUpdate.onStart(update_started);
    ESPhttpUpdate.onEnd(update_finished);
    ESPhttpUpdate.onProgress(update_progress);
    ESPhttpUpdate.onError(update_error);
    
    t_httpUpdate_return ret = ESPhttpUpdate.update("http://" + updateAddr.toString() + ":8266");

    Serial.println("http://" + updateAddr.toString());

    switch (ret) 
    {
      case HTTP_UPDATE_FAILED:
        Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
        break;

      case HTTP_UPDATE_NO_UPDATES:
        Serial.println("HTTP_UPDATE_NO_UPDATES");
        break;

      case HTTP_UPDATE_OK:
        Serial.println("HTTP_UPDATE_OK");
        break;
    }

    
  }

  //DateTime rtctime = rtc.now();

  if (millis() - otime > 5000)
  {
    if (localTime.tm_year < (2019 - 1900) && !bNeedInit)
    {
      otime = millis();
      Serial.println("get ntp time...");
      getNtpTime();
    }
  }
  
  
  
  if (bNeedInit)
    dnsServer.processNextRequest();
  
  display.loop();
  http_loop();
  udpServer.udp_loop();
  delay(1);
}
