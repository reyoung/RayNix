#ifndef KERNEL_DRIVER_IO_H_INCLUDED
#define KERNEL_DRIVER_IO_H_INCLUDED

#define outb(Port,Value)\
	__asm("outb %%al,%%dx;"::"d"(Port),"a"(Value))










#endif