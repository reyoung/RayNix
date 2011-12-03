#ifndef KERNEL_DRIVER_CONSOLE_H_INCLUDED
#define KERNEL_DRIVER_CONSOLE_H_INCLUDED
#include "stdint.h"

boolean Console_Init();
boolean Console_GotoXY(int x, int y);
boolean Console_IsVideoMono();
boolean Console_PutCharWithColor(char ch,char color);



















#endif
