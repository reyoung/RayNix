#ifndef KERNEL_DRIVER_INLINEASM_H
#define KERNEL_DRIVER_INLINEASM_H

#include "io.h"

#define cli					__asm__ __volatile__ ("cli")
#define sti					__asm__ __volatile__ ("sti")
#define enter_critical_region			cli
#define leave_critical_region			sti
	


#endif
