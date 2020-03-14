#ifndef DISPLAY_H
#define DISPLAY_H

class Display
{
public:
  struct SysInfo
  {

    char cpuClock[4];
    int cpuLoad;
    char cpuTemp[4];
    char cpuSpeed[5];
    char cpuVolt[5];
    char cpuPower[7];

    char gpuClock[4];
    int gpuLoad;
    char gpuTemp[4];
    char gpuSpeed[5];
    char gpuVolt[5];

    int memUsage;
    int vmemUsage;
    char boardTemp[4];
    int gpuTDP;

    int hddCount;
    int hddTemp[2];
    SysInfo()
    {
      this->hddCount = 0;
    }
  };
  
  Display();
  void init();
  void showTest();
  void drawXBM(uint8_t width, uint8_t height, uint8_t *bmp);
  int printf(const char *format, ...);
  void loop();
  void drawHome();
  void drawDashBorad();
  void clearDisplay();
  void refresh();
  SysInfo info;
  

private:
  uint _strPos;
  uint _fontSize;
  uint _displayTime;
  uint _freeTime;
};

#endif
