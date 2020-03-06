#include "esp8266_iot.h"
#include "display.h"


#define SCL 4
#define SDA 5

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);
unsigned long dtime = 0;



Display::Display()
{
  this->_strPos = 0;
  this->_fontSize = 0;
}

void Display::init()
{
  u8g2.begin();
  u8g2.setFont(u8g2_font_tom_thumb_4x6_tf); 
  this->_fontSize = 12;
  this->_strPos = this->_fontSize;
  u8g2.enableUTF8Print();	
}


int Display::printf(const char * format, ...)
{
  
  u8g2.setDrawColor(1);
  u8g2.setFont(u8g2_font_helvB08_te); 
  this->_fontSize = 9;

  if (this->_strPos + this->_fontSize > 64)
  {
    this->_strPos = this->_fontSize;
    //this->clearDisplay();
    u8g2.firstPage();
  }
  
  char* str = new char[256];
  va_list ap;
  int ret = -1;
  va_start(ap, format);
  ret = vsprintf(str, format, ap);
  va_end(ap);
  
  do 
  {
    u8g2.drawStr(0, this->_strPos, str); 
  }
  while (u8g2.nextPage());

  //u8g2.clearBuffer();
  
  //u8g2.sendBuffer();
  this->_strPos += this->_fontSize;
  delete[] str;
  return ret;
}

void Display::showTest()
{

  u8g2.setDrawColor(1);

  u8g2.clearBuffer();

  u8g2.drawXBMP(0, 15, cpu_icon_width, cpu_icon_height, cpu_icon_bits);
  u8g2.drawXBMP(25, 15, gpu_icon_width, gpu_icon_height, gpu_icon_bits);
  u8g2.drawXBMP(50, 15, mem_icon_width, mem_icon_height, mem_icon_bits);
  u8g2.drawXBMP(75, 15, fan_icon_width, fan_icon_height, fan_icon_bits);
  u8g2.drawXBMP(100, 15, hdd_icon_width, hdd_icon_height, hdd_icon_bits);
  
  char* buf = new char[32];

  sprintf(buf, "%d-%02d-%02d %02d:%02d:%02d", (localTime.tm_year) + 1900, (localTime.tm_mon) + 1, localTime.tm_mday, localTime.tm_hour, localTime.tm_min, localTime.tm_sec);
  u8g2.drawStr(0, 12, buf); 


  //u8g2.setCursor(0, 15);
  //u8g2.print("Hello World!");
  //u8g2.setCursor(0, 40);
  //u8g2.print("你好世界");	


  u8g2.sendBuffer();



}

void Display::clearDisplay()
{
  u8g2.clearDisplay();
}




void Display::drawBmp(uint8_t width, uint8_t height, uint8_t* bmp)
{
  u8g2.setDrawColor(0);
  u8g2.setBitmapMode(false);
  u8g2.clearBuffer();
  u8g2.drawXBM(0, 0, width, height, bmp);
  u8g2.sendBuffer();


}
