#include "CMOS.h"
#include "InlineASM.h"

static char Buffer[128];

void CMOS_ReadAll(uint8_t* buffer){
	uint8_t tvalue=0, index=0;
	for(index = 0;index<128;++index){
		cli;
		outb(0x70,index);
		tvalue = inb(0x71);
		sti;

		buffer[index] = tvalue;
	}
}
void CMOS_Write(uint8_t* buffer){
	uint8_t i;
	for(i=0;i<128;++i){
		cli;
		outb(0x70,i);
		outb(0x71,buffer[i]);
		sti;
	}
}


void CMOS_GetCurrentDateTime(CMOS_DateTime* dt){
	CMOS_ReadAll(Buffer);
	uint8_t sb = Buffer[CMOS_STATE_B_OFFSET];
	dt->Hour = Buffer[CMOS_HOUR_OFFSET];
	dt->Min = Buffer[CMOS_MIN_OFFSET];
	dt->Second = Buffer[CMOS_SECOND_OFFSET];

	dt->Day  = Buffer[CMOS_DAY_OF_MONTH_OFFSET];
	dt->Month = Buffer[CMOS_MONTH_OFFSET];
	dt->Year = Buffer [CMOS_YEAR_OFFSET];
	if(!(sb&CMOS_DATE_ISBINARY)){
#define AjustBCD(T)\
do{\
	int8_t temp = dt->T;\
	dt->T = temp&0x0F;\
	temp=temp&0xF0;\
	temp>>=4;\
	temp&=0x0F;\
	dt->T += temp *10;\
}while(0)
		AjustBCD(Hour);
		AjustBCD(Min);
		AjustBCD(Second);
		AjustBCD(Day);
		AjustBCD(Month);
		AjustBCD(Year);

#undef AjustBCD

	}
}

