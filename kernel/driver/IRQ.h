#ifndef KERNEL_DRIVER_IRQ_H
#define KERNEL_DRIVER_IRQ_H

struct ISR_Regs;
void IRQ_Init();
void IRQ_InstallHandler(int irq,void (*func)(struct ISR_Regs * r));
#define IRQ_UninstallHandler(irq)\
	IRQ_InstallHandler(irq,0)

void* IRQ_GetHandler(int irq);

#endif
