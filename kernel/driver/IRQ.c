#include "ISR.h"
#include "io.h"
#include "console.h"
#include "InlineASM.h"

typedef void(* CallbackType )(struct ISR_Regs* );

static CallbackType __handlers[16] = {
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0
};


void IRQ_Init(){
	outb(0x20,0x11);
	outb(0xA0,0x11);
	outb(0x21,0x20);
	outb(0xA1,0x28);
	outb(0x21,0x04);
	outb(0xA1,0x02);
	outb(0x21,0x01);
	outb(0xA1,0x01);
	outb(0x21,0);
	outb(0xA1,0);
	sti;
}
void IRQ_InstallHandler(int irq,void (*func)(struct ISR_Regs * r)){
	if(irq>=16 || irq < 0)
		return ;
	
	enter_critical_region;
	__handlers[irq]=func;
	leave_critical_region;
}

void* IRQ_GetHandler(int irq){
	if(irq>=16 || irq < 0){
		return __handlers[irq];
	} else {
		return 0;
	}
}

void ___IRQ_Handler(struct ISR_Regs* reg ){
	int index = reg->int_no - 32;
	if(index>=0 && index<=15){
		if(__handlers[index]){
			__handlers[index](reg);
		}
	}
	if(reg->int_no >= 40){
		outb(0xA0,0x20);
	}
	outb(0x20,0x20);
}


