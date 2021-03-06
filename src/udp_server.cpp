#include "esp8266_iot.h"
#include "udp_server.h"



uint32_t udp_port = 8266;
char rxBuffer[UDP_TX_PACKET_MAX_SIZE + 1];
WiFiUDP udp_server;
unsigned long utime = 0;
UdpServer::Packet* UdpServer::buildPacket(char cmd, const char *buf /*= NULL*/, int len /*= 0*/)
{
  UdpServer::Packet *p = new UdpServer::Packet;
  p->cmd = cmd;
  p->ver = 1;
  p->len = len;

  if (buf)
    memcpy(p->data, buf, len);
  return p;
}
void UdpServer::sendPacket(UdpServer::Packet *p, IPAddress ip, uint32_t port)
{
  udp_server.beginPacket(ip, port);
  udp_server.write((char *)p, p->len + 4);
  udp_server.endPacket();
  delete p;
}
void UdpServer::udp_loop()
{
  UdpServer::Packet *p;
  if (millis() - utime > 5000)
  {
    String md5 = ESP.getSketchMD5();
    p = buildPacket(PACKET_ALIVE, md5.c_str(), 32);
    sendPacket(p, IPAddress(255, 255, 255, 255), udp_port);
    utime = millis();
  }
  int packetSize = udp_server.parsePacket();
  if (packetSize)
  {
    int n = udp_server.read(rxBuffer, UDP_TX_PACKET_MAX_SIZE);
    rxBuffer[n] = 0;

    UdpServer::Packet rxp;
    unsigned short len = 0;
    memcpy(&len, rxBuffer + 2, 2);

    if (n > (len + 4))
      return;
/*
    Serial.printf("Received packet of size %d from %s:%d\n    (to %s:%d, free heap = %d B)\n",
                  packetSize,
                  udp_server.remoteIP().toString().c_str(), udp_server.remotePort(),
                  udp_server.destinationIP().toString().c_str(), udp_server.localPort(),
                  ESP.getFreeHeap());
*/
    memcpy(&rxp, rxBuffer, n);
    switch (rxp.cmd)
    {
      case PACKET_UPDATE:
      {
        p = buildPacket(PACKET_UPDATE);
        sendPacket(p, udp_server.remoteIP(), udp_server.remotePort());
        updateAddr = udp_server.remoteIP();
        bNeedUpdate = true;
        break;
      }
      case PACKET_REBOOT:
      {
        p = buildPacket(PACKET_REBOOT);
        sendPacket(p, udp_server.remoteIP(), udp_server.remotePort());
        ESP.restart();
        break;
      }
      case PACKET_RESET:
      {
        LittleFS.format();
        p = buildPacket(PACKET_RESET);
        sendPacket(p, udp_server.remoteIP(), udp_server.remotePort());
        delay(1000);
        ESP.restart();
        break;
      }
      case PACKET_TOGGLE_LED:
      {
        char cled = digitalRead(LED_BUILTIN);
        digitalWrite(LED_BUILTIN, !cled);
        p = buildPacket(PACKET_TOGGLE_LED, (char *)&cled, 1);
        sendPacket(p, udp_server.remoteIP(), udp_server.remotePort());
        break;
      }
      case PACKET_TOGGLE_DISPLAY:
      {
        /*
        bDisplay = !bDisplay;
        char ti = bDisplay ? 1 : 0;
        if (bDisplay)
          display.showTest();
        else
          display.clearDisplay();
        p = buildPacket(PACKET_TOGGLE_DISPLAY, (char *)&ti, 1);
        sendPacket(p, udp_server.remoteIP(), udp_server.remotePort());
        break;
        */
      }
      case PACKET_GET_INFO:
      {
        char buf[32] = {0};
        int len = sprintf(buf, "freemem:%d", ESP.getFreeHeap());
        p = buildPacket(PACKET_GET_INFO, buf, len);
        sendPacket(p, udp_server.remoteIP(), udp_server.remotePort());
        break;
      }
      case PACKET_DISPLAY_IMG:
      {
        uint8_t *bmp = new uint8_t[rxp.len];
        uint8_t width, height;
        memcpy(&width, rxp.data, 1);
        memcpy(&height, rxp.data + 1, 1);
        memcpy(bmp, rxp.data + 2, rxp.len - 2);
        display.drawXBM(width, height, bmp);
        delete[] bmp;
        display.refresh();
        tDisplay = 2;
        break;
      }
      case PACKET_DISPLAY_INFO:
      {
        char *js = new char[rxp.len];
        memcpy(js, rxp.data, rxp.len);
        JSONVar jo = JSON.parse(js);
    
        if (JSON.typeof(jo) == "undefined")
          return;
        
        
        const char* cpuClock = jo["SCPUCLK"];
        const char* cpuLoad = jo["SCPUUTI"];
        const char* cpuTemp = jo["TCPU"];
        const char* cpuSpeed = jo["FCPU"];
        const char* cpuVolt = jo["VCPU"];
        const char* cpuPower = jo["PCPUPKG"];
        const char* gpuClock = jo["SGPU1CLK"];
        const char* gpuLoad = jo["SGPU1UTI"];
        const char* gpuTemp = jo["TGPU1DIO"];
        const char* gpuSpeed = jo["FGPU1"];
        const char* gpuVolt = jo["VGPU1"];
        const char* memUsage = jo["SMEMUTI"];
        const char* vmemUsage = jo["SVMEMUSAGE"];
        const char* boardTemp = jo["TMOBO"];  
        const char* gpuTDP = jo["PGPU1TDPP"];
        


        Display::SysInfo sysInfo;
        if (cpuClock)
        {
          int clock = atoi(cpuClock);
          sprintf(sysInfo.cpuClock, "%1.1f", ((float)clock / 1000));
        }
        if (cpuLoad)
          sysInfo.cpuLoad = atoi(cpuLoad);
        if (cpuTemp)
          strcpy(sysInfo.cpuTemp, cpuTemp);
        if (cpuSpeed)
          strcpy(sysInfo.cpuSpeed, cpuSpeed);
        if (cpuVolt)
        {
          double volt = atof(cpuVolt);
          sprintf(sysInfo.cpuVolt, "%1.1f", volt);
        }
        if (cpuPower)
        {
          double power = atof(cpuPower);
          sprintf(sysInfo.cpuPower, "%3.0f", power);
        }
        if (gpuClock)
        {
          int clock = atoi(gpuClock);
          sprintf(sysInfo.gpuClock, "%1.1f", ((float)clock / 1000));
        }
        if (gpuLoad)
          sysInfo.gpuLoad = atoi(gpuLoad);
        if (gpuTemp)
          strcpy(sysInfo.gpuTemp, gpuTemp);
        if (gpuSpeed)
          strcpy(sysInfo.gpuSpeed, gpuSpeed);
        if (gpuVolt)
        {
          double volt = atof(gpuVolt);
          sprintf(sysInfo.gpuVolt, "%1.1f", volt);
        }
        if (memUsage)
          sysInfo.memUsage = atoi(memUsage);
        if (vmemUsage)
          sysInfo.vmemUsage = atoi(vmemUsage);
        if (boardTemp)
          strcpy(sysInfo.boardTemp, boardTemp);
        if (gpuTDP)
          sysInfo.gpuTDP = atoi(gpuTDP);  

        
        if (jo.hasOwnProperty("hl"))
        {
          int hddCount = atoi(jo["hl"]);
          if (hddCount <= 0)
            return;
          int saveCount = 0;
          sysInfo.hddCount = hddCount;
          for(int i = 0; i < hddCount; i++)
          {
            char hddName[6];
            sprintf(hddName, "THDD%d", i + 1);
            const char* hdds = jo[hddName];
            if (saveCount >= 2)
              break;
            if (hdds)
            {
              sysInfo.hddTemp[saveCount] = atoi(hdds);
              saveCount++;
            }

          }
        }
        memcpy(&display.info, &sysInfo, sizeof(Display::SysInfo));
        tDisplay = 1;
        display.refresh();
        delete[] js;
        break;
      }
    }
  }
}
