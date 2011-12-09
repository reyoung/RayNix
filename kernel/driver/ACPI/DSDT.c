#include "DSDT.h"
#include "FADT.h"
#include "../console.h"
#include "../timer.h"
ACPI_DSDT_Header* ACPI_DSDT_GetHeader(){
	if(ACPI_FADT_IsValid()){
		ACPI_FADT* fadt = ACPI_FADT_GetInstance();
		return fadt->Dsdt;
	} else {
		return 0;
	}
}
uint16_t ACPI_DSDT_S5_Get_SLP_TYPa(){
	uint8_t* s5 = ACPI_DSDT_GetS5Object();
	s5+=5;
	s5+=((*s5&0xC0)>>6)+2;
	if(*s5==0x0A)
		++s5;
	uint16_t retv = (*(s5))<<10;
	return retv;
}
uint16_t ACPI_DSDT_S5_Get_SLP_TYPb(){
	uint8_t* s5 = ACPI_DSDT_GetS5Object();
	s5+=5;
	s5+=((*s5&0xC0)>>6)+2;
	if(*s5==0x0A)
		++s5;
	++s5;
	if(*s5==0x0A)
		++s5;
	uint16_t retv = ((*s5))<<10;
	return retv;
}

void*  ACPI_DSDT_GetS5Object(){
	ACPI_DSDT_Header* h = ACPI_DSDT_GetHeader();
	uint8_t* p = (void*)(h)+sizeof(ACPI_DSDT_Header);
	size_t l = h->Length - sizeof(ACPI_DSDT_Header);
	for(size_t i=0;i<l;++i){
		if(strncmp(&p[i],"_S5_",4)==0){
			return &p[i];
		}
	}
	return 0;
}


boolean ACPI_DSDT_IsValid(){
	ACPI_DSDT_Header* h = ACPI_DSDT_GetHeader();
	if(h){
		if(strncmp(h->Signature,"DSDT",4)==0){
			uint8_t cksum = 0;
			uint8_t* p = h;
			for(int i=0;i<h->Length;++i){
				cksum+=p[i];
			}
			return cksum ==0;
		} else {
			return False;
		}
	} else {
		return False;
	}
}

void ACPI_DSDT_Dump(){
	if(ACPI_DSDT_IsValid()){
		ACPI_DSDT_Header* h = ACPI_DSDT_GetHeader();
		uint8_t* p = (void*)(h)+sizeof(ACPI_DSDT_Header);
		size_t count = h->Length - sizeof(ACPI_DSDT_Header);
		boolean hltFlag = False;
		for(size_t i=0;i<count;++i){
			if(strncmp(&p[i],"_S5_",4)==0){
				Console_Clear();
				Console_Printf("S5 Founded!\r\n");
				Timer_Sleep(25000);
				hltFlag = 1;
			}
			Console_PutChar(p[i]);

			if((i+1)%512==0){
				if(hltFlag){
					for(;;);
				}
			}	
		}
	} else {
		Console_Printf("Dsdt Is not valid!!!\r\n");
	}
}
