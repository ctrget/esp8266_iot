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

void Display::DrawHXBM(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t width, u8g2_uint_t blen, const uint8_t *b)
{
  uint8_t mask;
  mask = 1;

  x = width - 1;
  int i = 0;

Serial.printf("line %d|\r", y);

  while (blen > 0)
  {
    for (int i = 0; i < 8; i++)
    {
      
      if ( *b & mask )
      {
        u8g2.drawHLine(x, y, 1);
      }

      mask <<= 1;
      x--;

    }

    Serial.printf("%#X", *b);
    blen--;
    mask = 1;
    b++;
  }

Serial.println("|");
/*
  while (len > 0)
  {
    //Serial.printf("print hline y:%d  line%d\r", y, len);

    if ( *b & mask )
    {

      u8g2.drawHLine(x, y, 1);

    }

    x--;
    mask <<= 1;

    if ( mask == 0 )
    {
      mask = 1;
      b++;
    }

    len--;
  }
*/

  /*
    while (len > 0)
    {
     if ( *b & mask )
     {
       u8g2.drawHLine(x, y, 1);
     }

     x++;
     mask <<= 1;

     if ( mask == 0 )
     {
       mask = 1;
       b++;
     }

     len--;
    }
  */

}

void Display::drawXBM(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h, const uint8_t *bitmap)
{
  u8g2_uint_t blen;
  blen = (w / 8 + 3) / 4 * 4;
  //blen = w;
  //blen += 7;
  //blen >>= 3;

  

  y = h - 1;


  while ( h > 0 )
  {
    this->DrawHXBM(x, y, w, blen, bitmap);
    bitmap += blen;
    y--;
    h--;
  }

  /*
    while ( h > 0 )
    {
    this->DrawHXBM(x, y, w, bitmap);
    bitmap += blen;
    y++;
    h--;
    }

  */
}


void Display::drawBmp(uint8_t* bmp)
{
  u8g2.clearBuffer();
  this->drawXBM(0, 0, 88, 64, bmp);
  u8g2.sendBuffer();


}
