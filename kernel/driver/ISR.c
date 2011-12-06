#include "ISR.h"
#include "console.h"
void ___ISR_Handler(struct ISR_Regs* reg){
	if(reg->int_no < 32){
		Console_Printf("Exception %d\r\n",reg->int_no);
		for(;;);
	}
}
