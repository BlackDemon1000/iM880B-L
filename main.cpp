//-------------------------------------------------------------------------
-----
//
// File: main.cpp
//
// Abstract: main module
//
// Version: 0.1
//
// Date: 18.05.2016
//
// Disclaimer: This example code is provided by IMST GmbH on an "AS IS"
// basis without any warranties.
//
//-------------------------------------------------------------------------
-----
//-------------------------------------------------------------------------
-----
//
// Include Files
//
//-------------------------------------------------------------------------
-----
#include "WiMOD_LoRaWAN_API.h"
#include <conio.h>
#include <stdio.h>
//-------------------------------------------------------------------------
-----
//
// Declarations
//
//-------------------------------------------------------------------------
-----
// forward declarations
static void ShowMenu();
static void Ping();
static void SendUData();
static void SendCData();
//-------------------------------------------------------------------------
-----
//
// Section Code
//
//-------------------------------------------------------------------------
-----
//-------------------------------------------------------------------------
-----
//
// main
//
//-------------------------------------------------------------------------
-----
int
main(int argc, char *argv[])
{
 bool run = true;
 // show menu
 ShowMenu();
 // init interface
 WiMOD_LoRaWAN_Init("COM128");
 // main loop
 while(run)
 {
 // handle receiver process
 WiMOD_LoRaWAN_Process();
 // keyboard pressed ?
 if(kbhit())
 {
 // get command
 char cmd = getch();
 // handle commands
 switch(cmd)
 {
 case 'e':
 case 'x':
 run = false;
 break;
 case 'p':
 // ping device
 Ping();
break;
 case 'u':
 // send u-data
 SendUData();
break;
 case 'c':
 // send c-data
 SendCData();
break;
 case ' ':
 ShowMenu();
break;
 }
 }
 }
 return 1;
}
//-------------------------------------------------------------------------
-----
//
// ShowMenu
//
// @brief: show main menu
//
//-------------------------------------------------------------------------
-----
void
ShowMenu()
{
 printf("\n\r");
 printf("------------------------------\n\r");
 printf("[SPACE] : show this menu\n\r");
 printf("[p] : ping device\n\r");
 printf("[u] : send unconfirmed radio message\n\r");
 printf("[c] : send confirmed radio message\n\r");
 printf("[e|x] : exit program\n\r");
 printf("\n\r-> enter command: ");
}
//-------------------------------------------------------------------------
-----
//
// Ping
//
// @brief: ping device
//
//-------------------------------------------------------------------------
-----
void
Ping()
{
 printf("Ping Device\n\r");
 WiMOD_LoRaWAN_SendPing();
}
//-------------------------------------------------------------------------
-----
//
// SendUData
//
// @brief: send unconfirmed radio message
//
//-------------------------------------------------------------------------
-----
void
SendUData()
{
 // port 0x21
 UINT8 port = 0x21;
 UINT8 data[4];
 data[0] = 0x01;
 data[1] = 0x02;
 data[2] = 0x03;
 data[3] = 0x04;
 // send unconfirmed radio message
 WiMOD_LoRaWAN_SendURadioData(port, data, 4);
}
//-----------------------------------------------------------------------
-------
//
// SendCData
//
// @brief: send confirmed radio message
//
//-------------------------------------------------------------------------
-----
void
SendCData()
{
 // port 0x21
 UINT8 port = 0x23;
 UINT8 data[6];
 data[0] = 0x0A;
 data[1] = 0x0B;
 data[2] = 0x0C;
 data[3] = 0x0D;
 data[4] = 0x0E;
 data[5] = 0x0F;
 // send unconfirmed radio message
 WiMOD_LoRaWAN_SendCRadioData(port, data, 6);
}
//-------------------------------------------------------------------------
-----
// end of file
//-------------------------------------------------------------------------
-----