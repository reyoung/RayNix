#ifndef KERNEL_DRIVER_TIMER_H
#define KERNEL_DRIVER_TIMER_H
#include "stddef.h"

struct ISR_Regs;

void Timer_Init();

void Timer_AppendOnTickListener(void(*listener)(struct ISR_Regs*));

boolean Timer_RemoveOnTickListener(void(*listener)(struct ISR_Regs*));

void Timer_Sleep(int ms);

#endif
