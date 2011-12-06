#ifndef KERNEL_DRIVER_MM_PAGE_H
#define KERNEL_DRIVER_MM_PAGE_H
#include "stdint.h"
uint32_t* MM_PAGE_GetPageDirectoryBaseAddr();

void MM_PAGE_Init();



#endif
