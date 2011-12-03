#ifndef KERNEL_DRIVER_CONSOLE_H_INCLUDED
#define KERNEL_DRIVER_CONSOLE_H_INCLUDED
#include "stdint.h"

boolean Console_Init();
boolean Console_GotoXY(int x, int y);
boolean Console_IsVideoMono();
boolean Console_PutCharWithColor(char ch,char color);
boolean Console_SetDefaultColor(char color);
boolean Console_PutChar(char ch);
boolean Console_PutString(const char * str);
boolean Console_Clear();
boolean Console_ScorllPage();


















#endif
