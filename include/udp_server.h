#ifndef UDP_SERVER
#define UDP_SERVER

#include <WiFiUdp.h>

extern WiFiUDP udp_server;
extern unsigned int udp_port;

#define PACKET_ALIVE 0X0
#define PACKET_OK    0X1
#define PACKET_FAIL  0X2
#define PACKET_UPDATE  0X3
#define PACKET_DEBUG 0X4


#define PACKET_DISPLAY_IMG     0XF
#define PACKET_DISPLAY_INFO    0X10
#define PACKET_GET_INFO        0X11
#define PACKET_TOGGLE_LED      0X12
#define PACKET_TOGGLE_DISPLAY  0X13
#define PACKET_REBOOT          0X14
#define PACKET_RESET           0X15

class UdpServer
{
public:
  struct Packet
  {
    unsigned char cmd;
    char ver;
    unsigned short len;
    unsigned char data[2048];
  };



  void udp_loop();
  void sendPacket(UdpServer::Packet *p, IPAddress ip, uint32_t port);
  UdpServer::Packet* buildPacket(char cmd, const char *buf = NULL, int len = 0);


};

#endif
