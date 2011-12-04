#ifndef RLIBC_VSPRINTF_H
#define RLIBC_VSPRINTF_H
#include "stdarg.h"

int sprintf(char * str, const char * fmt, ...);
int vsprintf(char* str,const char* fmt,va_list args);

#endif
