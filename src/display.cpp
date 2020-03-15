#include "esp8266_iot.h"
#include "display.h"
/*
//SPI
   ESP8266 ---  OLED
     3V    ---  VCC
     G     ---  GND
     D7    ---  D1
     D5    ---  D0
     D2orD8---  CS
     D1    ---  DC
     RST   ---  RES
//IC2
     OLED  ---  ESP8266
     VCC   ---  3.3V / 5V
     GND   ---  G (GND)
     SCL   ---  D1(GPIO5)
     SDA   ---  D2(GPIO4)
*/
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
unsigned long dtime = 0;
HTTPClient http;
char weatherUrl[96];

Display::Display()
{
  this->_strPos = 0;
  this->_fontSize = 0;
  this->_displayTime = 0;
  this->_freeTime = 0;
}
void Display::init()
{
  u8g2.begin();
  u8g2.setFont(u8g2_font_wqy12_t_gb2312a);
  this->_fontSize = 9;
  this->_strPos = this->_fontSize;
  u8g2.enableUTF8Print();
}

void Display::ready()
{
  char appid[16];
  char appsecret[16] ;
  
  if (!(readConfig("/config.json", "weather_appid", appid) && readConfig("/config.json", "weather_appsecret", appsecret)))
  {
    Serial.println("Weather read config error!");
    return;
  }

  sprintf(weatherUrl, "http://tianqiapi.com/api?version=v6&appid=%s&appsecret=%s", appid, appsecret);
  Serial.println(weatherUrl);
  getWeather();
}

int Display::printf(const char *format, ...)
{
  u8g2.setDrawColor(1);
  if (this->_strPos + this->_fontSize > 64)
  {
    this->_strPos = this->_fontSize;
    u8g2.firstPage();
  }
  char *str = new char[256];
  va_list ap;
  int ret = -1;
  va_start(ap, format);
  ret = vsprintf(str, format, ap);
  va_end(ap);
  do
  {
    u8g2.drawStr(0, this->_strPos, str);
  } while (u8g2.nextPage());

  this->_strPos += this->_fontSize;
  delete[] str;
  return ret;
}



void Display::clearDisplay()
{
  u8g2.clearDisplay();
}

void Display::refresh()
{
  this->_freeTime = millis();
}


void Display::getWeather()
{


  String json = "";



  Serial.print("[HTTP] begin...\n");

    if (http.begin(weatherUrl)) 
    {

      Serial.print("[HTTP] GET...\n");
      int httpCode = http.GET();


      if (httpCode > 0)
      {

        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
        {
          
          json = http.getString();
          
          JSONVar jo = JSON.parse(json);
    
          if (JSON.typeof(jo) != "undefined")
          {
            if (jo.hasOwnProperty("errcode"))
              return;
            Serial.println(json);
            strcpy(weather.city, jo["city"]);
            strcpy(weather.wea, jo["wea"]);
            strcpy(weather.tem, jo["tem"]);
            weather.time = millis();

          }


        }
      }
      else
      {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } 
    else 
    {
      Serial.printf("[HTTP} Unable to connect\n");
    }


}

void Display::drawHome()
{

  u8g2.firstPage();
  u8g2.setDrawColor(1);
  u8g2.setFont(u8g2_font_wqy12_t_gb2312a);
  do
  {
    char *nowdata = new char[32];
    char *nowtime = new char[32];

    if (weather.time > 0)
    {
      String tem = String(weather.tem) + "℃";
      //城市 天气情况
      u8g2.setFont(u8g2_font_wqy12_t_gb2312a);
      u8g2.drawUTF8(5, 58, weather.city);
      u8g2.drawUTF8(85, 58, weather.wea);
      //温度
      u8g2.setFont(u8g2_font_wqy13_t_gb2312a);
      u8g2.drawUTF8(52, 58, tem.c_str());
    }
    else
    {
      u8g2.drawUTF8(5, 58, "正在获取天气信息");
    }
    

    //获取时间
    sprintf(nowdata, "%d-%02d-%02d", (localTime.tm_year) + 1900, (localTime.tm_mon) + 1, localTime.tm_mday);
    sprintf(nowtime, " %02d:%02d:%02d", localTime.tm_hour, localTime.tm_min, localTime.tm_sec);
 
    u8g2.setFont(u8g2_font_wqy13_t_gb2312a);
    

    switch(localTime.tm_wday)
    {
      case 0:
        u8g2.drawUTF8(80, 16, "星期日");
      break;
      case 1:
        u8g2.drawUTF8(80, 16, "星期一");
      break;
      case 2:
        u8g2.drawUTF8(80, 16, "星期二");
      break;
      case 3:
        u8g2.drawUTF8(80, 16, "星期三");
      break;
      case 4:
        u8g2.drawUTF8(80, 16, "星期四");
      break;
      case 5:
        u8g2.drawUTF8(80, 16, "星期五");
      break;
      case 6:
        u8g2.drawUTF8(80, 16, "星期六");
      break;
    }

 
    //日期
    u8g2.setFont(u8g2_font_wqy16_t_gb2312a);
    u8g2.drawUTF8(0, 16, nowdata);
    //时间
    u8g2.setFont(u8g2_font_fub20_tn);
    u8g2.drawStr(0, 41, nowtime);
    u8g2.sendBuffer();
    //释放资源
    delete[] nowdata;
    delete[] nowtime;
  } while (u8g2.nextPage());
}

void Display::drawDashBorad()
{
  u8g2.firstPage();
  do
  {
    char *buf = new char[64];
    u8g2.setDrawColor(1);
    //时间
    u8g2.setFont(u8g2_font_wqy12_t_gb2312a);
    sprintf(buf, "%d-%02d-%02d %02d:%02d:%02d", (localTime.tm_year) + 1900, (localTime.tm_mon) + 1, localTime.tm_mday, localTime.tm_hour, localTime.tm_min, localTime.tm_sec);
    u8g2.drawUTF8(10, 8, buf);
    if (info.hddCount > 0)
    {
      if (this->_displayTime >= 10)
        this->_displayTime = 0;
      if (this->_displayTime < 5)
      {
        //CPU频率
        u8g2.setFont(u8g2_font_fur35_tn);
        u8g2.drawUTF8(0, 64, info.cpuClock);
        u8g2.setFont(u8g2_font_wqy14_t_gb2312a);
        u8g2.drawUTF8(70, 64, "GHz");
        u8g2.setFont(u8g2_font_5x8_tf);
        //CPU使用率
        u8g2.drawUTF8(0, 16, "CPU%");
        u8g2.drawRFrame(27, 10, 101, 5, 2);
        u8g2.drawBox(28, 10, info.cpuLoad, 4);
        //内存使用率
        u8g2.drawUTF8(0, 24, "MEM%");
        u8g2.drawRFrame(27, 18, 101, 5, 2);
        u8g2.drawBox(28, 18, info.memUsage, 4);
        //CPU温度 风扇转速
        u8g2.setFont(u8g2_font_HelvetiPixel_tr);
        sprintf(buf, "%sC", info.cpuTemp);
        u8g2.drawUTF8(70, 35, buf);
        sprintf(buf, "%sR", info.cpuSpeed);
        u8g2.drawUTF8(95, 35, buf);
        //CPU电压 功耗
        sprintf(buf, "%sV", info.cpuVolt);
        u8g2.drawUTF8(70, 45, buf);
        sprintf(buf, "%sW", info.cpuPower);
        u8g2.drawUTF8(95, 45, buf);
        //主板温度 有用？？？
        sprintf(buf, "%sC", info.boardTemp);
        u8g2.drawUTF8(100, 55, buf);
      }
      else
      {
        //GPU频率
        u8g2.setFont(u8g2_font_fur35_tn);
        u8g2.drawUTF8(0, 64, info.gpuClock);
        u8g2.setFont(u8g2_font_wqy14_t_gb2312a);
        u8g2.drawUTF8(70, 64, "GHz");
        u8g2.setFont(u8g2_font_5x8_tf);
        //GPU使用率
        u8g2.drawUTF8(0, 16, "GPU%");
        u8g2.drawRFrame(27, 10, 101, 5, 2);
        u8g2.drawBox(28, 10, info.gpuLoad, 4);
        //显存使用率
        u8g2.drawUTF8(0, 24, "VRM%");
        u8g2.drawRFrame(27, 18, 101, 5, 2);
        u8g2.drawBox(28, 18, info.vmemUsage, 4);
        //GPU温度 风扇转速
        u8g2.setFont(u8g2_font_HelvetiPixel_tr);
        sprintf(buf, "%sC", info.gpuTemp);
        u8g2.drawUTF8(70, 35, buf);
        sprintf(buf, "%sR", info.gpuSpeed);
        u8g2.drawUTF8(105, 35, buf);
        //GPU电压 功耗
        sprintf(buf, "%sV", info.gpuVolt);
        u8g2.drawUTF8(70, 45, buf);
        sprintf(buf, "%dW", info.gpuTDP);
        u8g2.drawUTF8(105, 45, buf);
        if (info.hddCount > 0)
        {
          //硬盘1温度
          sprintf(buf, "%dC", info.hddTemp[0]);
          u8g2.drawUTF8(105, 55, buf);
        }
        if (info.hddCount > 1)
        {
          //硬盘2温度
          sprintf(buf, "%dC", info.hddTemp[1]);
          u8g2.drawUTF8(105, 64, buf);
        }
      }
      delete[] buf;
    }
  } while (u8g2.nextPage());
}

void Display::drawXBM(uint8_t width, uint8_t height, uint8_t *bmp)
{
  u8g2.setDrawColor(0);
  u8g2.setBitmapMode(false);
  u8g2.clearBuffer();
  u8g2.drawXBM(0, 0, width, height, bmp);
  u8g2.sendBuffer();
}

void Display::loop()
{

  if (millis() - dtime > 1000)
  {
    dtime = millis();
    getLocalTime();
    this->drawHome();

    if (dtime - weather.time > 60000)
      getWeather();

    /*
    if (millis() - this->_freeTime > 10000)
    {
      this->_freeTime = millis();
      bDisplay = false;
      display.clearDisplay();
    }
    if (bDisplay)
    {
      this->drawDashBorad();
      this->_displayTime++;
    }*/
  }
}