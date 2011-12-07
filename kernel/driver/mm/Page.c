#include "Page.h"
#include "../console.h"
extern uint32_t ___KernelEnd;


static uint8_t Mem_Page_USE_Map[1024*128]={0};



#define SET_MEM_USED(addr)\
	Mem_Page_USE_Map[(addr/4096)/8] |= (1<<((addr/4096)%8))

#define IS_MEM_USED(addr)\
	Mem_Page_USE_Map[(addr/4096)/8] & (1<<((addr/4096)%8))	


uint32_t* MM_PAGE_GetPageDirectoryBaseAddr(){
	uint32_t end = &___KernelEnd;
	uint32_t page_aligned_end = (end&0xFFFFF000)+0x1000;
	return page_aligned_end;
}

void MM_PAGE_Init(){
	uint32_t* PDB = MM_PAGE_GetPageDirectoryBaseAddr();
	for(int i=0;i<1024;++i){
		PDB[i]=0|2;
	}
	uint32_t address = 0;
	uint32_t* fpt = PDB+0x1000;
	for(int i=0;i<1024;++i){
		fpt[i] = address|3;
		address+=4096;
		SET_MEM_USED(address);
	}
	PDB[0] = fpt;
	PDB[0] |= 3;

	PDB[0x300] = fpt;
	PDB[0x300] |= 3;

	Console_Printf("Is Lowest 32k Used? %d\r\n",(int)Mem_Page_USE_Map[0]);

	__asm__ volatile("mov %0, %%cr3":: "b"(PDB));
	unsigned int cr0;
	__asm__ volatile("mov %%cr0, %0": "=b"(cr0));
	cr0 |= 0x80000000;
	__asm__ volatile("mov %0, %%cr0":: "b"(cr0));
	
}
