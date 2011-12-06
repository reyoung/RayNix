#ifndef KERNEL_DRIVER_IO_H_INCLUDED
#define KERNEL_DRIVER_IO_H_INCLUDED
#include "stdint.h"
#define outb(Port,Value)\
	__asm("outb %%al,%%dx;"::"d"(Port),"a"(Value))

#define outw(Port,Value)\
	__asm("outw %%ax,%%dx;"::"d"(Port),"a"(Value))

static inline
unsigned char inb( unsigned short port )
{
    unsigned char ret;
    __asm__ volatile( "inb %1, %0"
                  : "=a"(ret) : "Nd"(port) );
    return ret;
}









#endif
