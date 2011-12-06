#include "ISR.h"
#include "io.h"
#include "console.h"
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
	__asm__ __volatile__ ("sti");
}


void ___IRQ_Handler(struct ISR_Regs* reg ){
	Console_Printf("IRQ %d Handled.\r\n",reg->int_no-32);
	if(reg->int_no >= 40){
		outb(0xA0,0x20);
	}
	outb(0x20,0x20);
}


