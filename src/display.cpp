#include "esp8266_iot.h"
#include "display.h"

#define SCL 4
#define SDA 5

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);
unsigned long dtime = 0;



Display::Display()
{
  this->_bufferLen = 0;
}

void Display::init()
{
  u8g2.begin();
  //true 背景透明
  u8g2.setBitmapMode(false);
  u8g2.setDrawColor(1);
  //u8g2.setDisplayRotation(U8G2_R0);
}

void Display::showTest()
{

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 10, "Hello World!");
  u8g2.sendBuffer();



}

void Display::clearDisplay()
{
  u8g2.clearDisplay();
}




void Display::drawBmp(uint8_t width, uint8_t height, uint8_t* bmp)
{
  u8g2.clearBuffer();
  u8g2.drawXBM(0, 0, width, height, bmp);
  u8g2.sendBuffer();


}
