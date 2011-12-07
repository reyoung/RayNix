#ifndef KERNEL_DRIVER_MM_PAGE_H
#define KERNEL_DRIVER_MM_PAGE_H
#include "stdint.h"
#include "../ISR.h"
#include "../../multiboot.h"

uint32_t* MM_PAGE_GetPageDirectoryBaseAddr();

void MM_PAGE_Init(multiboot_info_t* mbd);

boolean MM_PAGE_IsInited();

void MM_PAGE_FaultHandler(struct ISR_Regs* reg);

#endif
