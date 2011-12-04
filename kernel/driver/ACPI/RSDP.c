#include "RSDP.h"
#include "string.h"
#define RSDP_MAGIC "RSD PTR "
#define RSDP_MAGIC_LEN 8
#define BIOS_MEM_BEGIN ((void*)(0x000E0000))
#define BIOS_MEM_END   ((void*)(0x000FFFFF))


int RSDP_GetVersion(){
	char * p = BIOS_MEM_BEGIN;
	while(p!=BIOS_MEM_END){
		if(strncmp(p,RSDP_MAGIC,RSDP_MAGIC_LEN)==0){
			return (int ) p[15]+1;
		}
		++p;
	}
	return -1;
}

void* RSDP_GetDescriptor(){
	char * p =BIOS_MEM_BEGIN;
	while(p!=BIOS_MEM_END){
		if(strncmp(p,RSDP_MAGIC,RSDP_MAGIC_LEN)==0){
			return p;
		}
		++p;
	}
	return 0;
}

boolean RSDP_IsValid(){
	void* addr = RSDP_GetDescriptor();
	char* v1 = addr;
	RSDP_Descriptor_V10* desc1 = addr;
	uint8_t c = 0;
	int i=0;
	for(;i<sizeof(RSDP_Descriptor_V10);++i){
		c+=*v1++;
	}
	if(desc1->Revision==0){
		return c==0;
	} else if(c!=0) {
		return False;
	} else {
		for(;i<sizeof(RSDP_Descriptor_V20)-sizeof(RSDP_Descriptor_V10);++i){
			c+=*v1++;
		}
		return c==0;
	}
}

