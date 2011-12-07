#include "ISR.h"
#include "console.h"
#include "InlineASM.h"

typedef void(*CallbackType)(struct ISR_Regs* );

static CallbackType funcs[32];


void ___ISR_Handler(struct ISR_Regs* reg){
	if(reg->int_no < 32){
		if(funcs[reg->int_no]){
			funcs[reg->int_no](reg);
		} else {
			Console_Printf("Exception %d\r\n",reg->int_no);
			for(;;);
		}
	}
}

void ISR_InstallHandler(int int_no, void(* func )(struct ISR_Regs* )){
	if(int_no < 32 && int_no >=0){
		enter_critical_region;
	
		funcs[int_no]=func;

		leave_critical_region;	
	}
}

