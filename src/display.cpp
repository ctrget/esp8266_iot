#include "esp8266_iot.h"
#include "display.h"


#define SCL 4
#define SDA 5

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);
unsigned long dtime = 0;



Display::Display()
{

}

void Display::init()
{
  u8g2.begin();
  //true 背景透明

  //u8g2.setDisplayRotation(U8G2_R0);
  u8g2.enableUTF8Print();	
}

void Display::showTest()
{

  u8g2.setDrawColor(1);
  u8g2.setFont(u8g2_font_wqy12_t_chinese2); 
  u8g2.clearBuffer();
  u8g2.setCursor(0, 15);
  u8g2.print("Hello World!");
  u8g2.setCursor(0, 40);
  u8g2.print("你好世界");	
  Serial.println("caaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

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
