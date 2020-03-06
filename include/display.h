#ifndef DISPLAY_H
#define DISPLAY_H




class Display
{
  public:
  Display();
  void init();
  void showTest();
  void drawBmp(uint8_t width, uint8_t height, uint8_t* bmp);
  void clearDisplay();
  private:
};


#endif
