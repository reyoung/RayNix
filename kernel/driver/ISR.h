#ifndef KERNEL_DRIVER_ISR_H
#define KERNEL_DRIVER_ISR_H
#include "stdint.h"
struct ISR_Regs{
	uint32_t gs, fs,es,ds;
	uint32_t edi,esi,ebp,esp,ebx,edx,ecx,eax;
	uint32_t int_no,err_code;
	uint32_t eip,cs,eflags,useresp,ss;
};



#endif
