#ifndef DISPLAY_H
#define DISPLAY_H

class Display
{
public:
  struct SysInfo
  {

    char cpuClock[4] = {0};
    int cpuLoad = 0;
    char cpuTemp[4] = {0};
    char cpuSpeed[5] = {0};
    char cpuVolt[5] = {0};
    char cpuPower[7] = {0};

    char gpuClock[4] = {0};
    int gpuLoad = 0;
    char gpuTemp[4] = {0};
    char gpuSpeed[5] = {0};
    char gpuVolt[5] = {0};

    int memUsage = 0;
    int vmemUsage = 0;
    char boardTemp[4] = {0};
    int gpuTDP = 0;

    int hddCount = 0;
    int hddTemp[2] = {0};

  };

  struct Weather
  {
    ulong time;
    char city[20];
    char wea[20];
    char tem[4];

    Weather()
    {
      this->time = 0;
    }

  };
  
  
  Display();
  void init();
  void ready();
  void loop();
  void drawXBM(uint8_t width, uint8_t height, uint8_t *bmp);
  int printf(const char *format, ...);
  void getWeather();
  void drawProgress(int progress, String caption);
  void drawHome();
  void drawDashBorad();
  void clearDisplay();
  void refresh();
  SysInfo info;
  Weather weather;
  

private:
  uint _strPos;
  uint _fontSize;
  uint _displayTime;
  uint _freeTime;
};

#endif
