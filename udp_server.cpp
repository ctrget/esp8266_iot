#include "esp8266_iot.h"
#include "udp_server.h"
#include <Hash.h>

uint32_t udp_port = 8266;
char rxBuffer[UDP_TX_PACKET_MAX_SIZE + 1];
WiFiUDP udp_server;
unsigned long utime = 0;

struct Packet
{
  unsigned char cmd;
  char ver;
  unsigned short len;
  unsigned char data[2048];
};


Packet* buildPacket(char cmd, char* buf = NULL, int len = 0)
{
  Packet* p = new Packet;
  p->cmd = cmd;
  p->ver = 1;
  p->len = len;

  if (buf)
    memcpy(p->data, buf, len);
  return p;
}

void sendPacket(Packet* p, IPAddress ip, uint32_t port)
{
  udp_server.beginPacket(ip, port);
  udp_server.write((char*)p, p->len + 4);
  udp_server.endPacket();
  delete p;
}


void udp_loop()
{
  Packet* p;

  if (millis() - utime > 5000)
  {

    p = buildPacket(0x0);
    sendPacket(p, IPAddress (255, 255, 255, 255), udp_port);
    utime = millis();
  }

  int packetSize = udp_server.parsePacket();

  if (packetSize)
  {

    int n = udp_server.read(rxBuffer, UDP_TX_PACKET_MAX_SIZE);
    rxBuffer[n] = 0;


    Packet rxp;
    unsigned short len = 0;
    memcpy(&len, rxBuffer + 2, 2);

    if (n > (len + 4))
      return;

    Serial.printf("Received packet of size %d from %s:%d\n    (to %s:%d, free heap = %d B)\n",
                  packetSize,
                  udp_server.remoteIP().toString().c_str(), udp_server.remotePort(),
                  udp_server.destinationIP().toString().c_str(), udp_server.localPort(),
                  ESP.getFreeHeap());

    //Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    //Serial.println(len);
    memcpy(&rxp, rxBuffer, n);



    switch (rxp.cmd)
    {
      case PACKET_REBOOT:
        {
          p = buildPacket(PACKET_REBOOT);
          sendPacket(p, udp_server.remoteIP(), udp_server.remotePort());
          ESP.restart();
          break;
        }

      case PACKET_TOGGLE_LED:
        {
          char cled = digitalRead(LED_BUILTIN);
          digitalWrite(LED_BUILTIN, !cled);
          p = buildPacket(PACKET_TOGGLE_LED, (char*)&cled, 1);
          sendPacket(p, udp_server.remoteIP(), udp_server.remotePort());
          break;
        }

      case PACKET_TOGGLE_DISPLAY:
      {
        bDisplay = !bDisplay;
        char ti = bDisplay ? 1 : 0;

        if (bDisplay)
          display.showTest();
        else
          display.clearDisplay();
        
        p = buildPacket(PACKET_TOGGLE_DISPLAY, (char*)&ti, 1);
        sendPacket(p, udp_server.remoteIP(), udp_server.remotePort());
        break;
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
        Serial.printf("data len : %d\n", rxp.len);
        uint8_t* bmp = new uint8_t[rxp.len];
        memcpy(bmp, rxp.data, rxp.len);

        /*
          uint8_t hash[20];
          sha1(bmp, rxp.len, &hash[0]);

          Serial.print("SHA1:");

          for (uint16_t i = 0; i < 20; i++) {
          Serial.printf("%02x", hash[i]);
          }
          Serial.println();
          Serial.printf("data is : %x %x %x %x \r", bmp[0], bmp[1], bmp[2], bmp[3]);
        */

        //display.sendBmp(bmp, rxp.len);

        display.drawBmp(bmp);
        delete[] bmp;
        break;

    }


  }

}
