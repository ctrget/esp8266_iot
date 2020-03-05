#ifndef DISPLAY_H
#define DISPLAY_H

#include <U8g2lib.h>

class Display
{
  public:
  Display();
  void init();
  void showTest();
  void drawBmp(uint8_t* bmp);
  void clearDisplay();
  void drawXBM(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h, const uint8_t *bitmap);
  void DrawHXBM(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t width, u8g2_uint_t blen, const uint8_t *b);
  private:
  uint32_t _bufferLen;
};


#endif
