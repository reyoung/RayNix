#include "Page.h"
extern uint32_t ___KernelEnd;

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
	uint32_t address = 0x0000;
	uint32_t* fpt = PDB+0x1000;
	for(int i=0;i<1024;++i){
		fpt[i] = address|3;
		address+=4096;
	}
	PDB[0] = fpt;
	PDB[0] |= 3;
	__asm__ volatile("mov %0, %%cr3":: "b"(PDB));
	unsigned int cr0;
	__asm__ volatile("mov %%cr0, %0": "=b"(cr0));
	cr0 |= 0x80000000;
	__asm__ volatile("mov %0, %%cr0":: "b"(cr0));
	
}
