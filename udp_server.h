#ifndef UDP_SERVER
#define UDP_SERVER

#include <WiFiUdp.h>

extern WiFiUDP udp_server;
extern unsigned int udp_port;

#define PACKET_ALIVE 0X0
#define PACKET_OK    0X1
#define PACKET_FAIL  0X2


#define PACKET_DISPLAY_IMG     0XF
#define PACKET_DISPLAY_INFO    0X10
#define PACKET_GET_INFO        0X11
#define PACKET_TOGGLE_LED      0X12
#define PACKET_TOGGLE_DISPLAY  0X13
#define PACKET_REBOOT          0X14



void udp_loop();

#endif
