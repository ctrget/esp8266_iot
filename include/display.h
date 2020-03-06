#ifndef DISPLAY_H
#define DISPLAY_H

#define cpu_icon_width 24
#define cpu_icon_height 24
static const unsigned char cpu_icon_bits[] U8X8_PROGMEM = {
  0x00, 0x00, 0x00, 0x20, 0xA5, 0x04, 0x20, 0xA5, 0x04, 0xA0, 0xA5, 0x05, 
  0xF0, 0xFF, 0x0F, 0x1E, 0x00, 0x78, 0x10, 0x00, 0x08, 0x18, 0x00, 0x18, 
  0x1E, 0x7E, 0x78, 0x10, 0xFF, 0x08, 0x1E, 0xC3, 0x78, 0x10, 0xC3, 0x08, 
  0x10, 0xC3, 0x08, 0x1E, 0xC3, 0x78, 0x10, 0xFF, 0x08, 0x1E, 0x7E, 0x78, 
  0x18, 0x00, 0x18, 0x10, 0x00, 0x08, 0x1E, 0x00, 0x78, 0xF0, 0xFF, 0x0F, 
  0xA0, 0xA5, 0x05, 0x20, 0xA5, 0x04, 0x20, 0xA5, 0x04, 0x00, 0x00, 0x00, 
  };


#define gpu_icon_width 24
#define gpu_icon_height 24
static const unsigned char gpu_icon_bits[] U8X8_PROGMEM  = {
  0x07, 0x00, 0x00, 0x06, 0x00, 0x00, 0x04, 0x00, 0x00, 0x06, 0x00, 0x00, 
  0x66, 0xFF, 0x3F, 0xF6, 0xFF, 0xFF, 0xE6, 0x03, 0xC0, 0xE6, 0x01, 0xC0, 
  0xE6, 0xF9, 0x9F, 0xE6, 0x79, 0x9C, 0xE6, 0x39, 0x98, 0xE6, 0xB9, 0x9B, 
  0xE6, 0xB9, 0x9B, 0xE6, 0x39, 0x98, 0xE6, 0x79, 0x9C, 0xE6, 0xF9, 0x9F, 
  0xE6, 0x01, 0xC0, 0xE6, 0x03, 0xC0, 0xE6, 0xFF, 0xFF, 0xE6, 0xFF, 0xFF, 
  0xE6, 0xFF, 0xFF, 0xC6, 0xB6, 0x6D, 0x46, 0x92, 0x24, 0x44, 0x92, 0x24, 
  };

#define mem_icon_width 24
#define mem_icon_height 24
static const unsigned char mem_icon_bits[] U8X8_PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x40, 
  0xC8, 0x18, 0x13, 0x36, 0x5A, 0x6C, 0xFE, 0xFF, 0x7F, 0xFE, 0xFF, 0x7F, 
  0xFE, 0xFF, 0x7F, 0x02, 0x0C, 0x40, 0x02, 0x0C, 0x00, 0xFE, 0xF3, 0x7F, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  };


#define fan_icon_width 24
#define fan_icon_height 24
static const unsigned char fan_icon_bits[] U8X8_PROGMEM = {
  0x80, 0x03, 0x00, 0xE0, 0x0F, 0x00, 0xF0, 0x0F, 0x06, 0xF8, 0x8F, 0x1F, 
  0xF8, 0xCF, 0x3F, 0xFC, 0xC7, 0x7F, 0xFC, 0xE7, 0xFF, 0xF8, 0xE7, 0xFF, 
  0xF8, 0xE7, 0xFF, 0xF0, 0xFF, 0xFF, 0xE0, 0xFF, 0xFF, 0x00, 0x67, 0x78, 
  0x1C, 0x66, 0x00, 0xFE, 0xFF, 0x03, 0xFF, 0xFF, 0x0F, 0xFF, 0xEF, 0x1F, 
  0xFF, 0xE7, 0x1F, 0xFE, 0xE7, 0x3F, 0xFE, 0xE7, 0x3F, 0xFC, 0xF3, 0x3F, 
  0xF8, 0xF1, 0x1F, 0xF0, 0xF0, 0x1F, 0x00, 0xE0, 0x0F, 0x00, 0xE0, 0x03, 
  };


#define hdd_icon_width 24
#define hdd_icon_height 24
static const unsigned char hdd_icon_bits[] U8X8_PROGMEM = {
  0x00, 0x00, 0x00, 0xF0, 0xFF, 0x0F, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 
  0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0xFC, 0xFF, 0x3F, 0xFC, 0xFF, 0x3F, 
  0xFC, 0xFF, 0x3F, 0xFC, 0xFF, 0x3F, 0xFC, 0xFF, 0x3F, 0xFE, 0xFF, 0x7F, 
  0xFE, 0xFF, 0x7F, 0xFE, 0xFF, 0x7F, 0xFE, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 
  0x00, 0x00, 0x00, 0xFE, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE1, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 
  };

#define power_icon_width 24
#define power_icon_height 24
static const unsigned char power_icon_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x01, 0x00, 0x80, 0x01, 
  0x00, 0xC0, 0x01, 0x00, 0xE0, 0x00, 0x00, 0xF0, 0x00, 0x00, 0xF8, 0x00, 
  0x00, 0x7C, 0x00, 0x00, 0x7E, 0x00, 0x00, 0xFF, 0x07, 0x80, 0xFF, 0x03, 
  0xE0, 0xFF, 0x01, 0xE0, 0xFF, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x3E, 0x00, 
  0x00, 0x1F, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x07, 0x00, 0x80, 0x03, 0x00, 
  0x80, 0x01, 0x00, 0xC0, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
  };



class Display
{
  public:
  Display();
  void init();
  void showTest();
  void drawBmp(uint8_t width, uint8_t height, uint8_t* bmp);
  int printf(const char * format, ...);
  void clearDisplay();
  private:
  uint _strPos;
  uint _fontSize;
};


#endif
