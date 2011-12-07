#include "Page.h"
#include "../console.h"
extern uint32_t ___KernelEnd;
static int PageTableCount = 0;
static boolean Inited = False;

uint32_t* MM_PAGE_GetPageDirectoryBaseAddr(){
	uint32_t end = &___KernelEnd;
	uint32_t page_aligned_end = (end&0xFFFFF000)+0x1000;
	return page_aligned_end;
}

boolean MM_PAGE_IsInited(){
	return Inited;
}

static void MapReservedHelper(uint32_t address,uint32_t pdbindex, uint32_t ptindex, uint32_t count){
	uint32_t* fp = 0;
	uint32_t* PDB = MM_PAGE_GetPageDirectoryBaseAddr();
	if( !(PDB[pdbindex] & 1)){ //! If The Page Directory's Page Table Isn't Present.
		++PageTableCount;
		fp = PDB + 0x1000 * PageTableCount;
		PDB[pdbindex]=fp;
		//PDB[PDB_Index]|=3;
	} else {
		fp = PDB[pdbindex];
	}

	for(uint32_t i = 0; i< count ;++i ){
		fp[ptindex+i] = address|3;
		address+= 0x1000;
	}
}


static void MapReserved(multiboot_memory_map_t* mmap ){
	uint32_t address = mmap->addr;
	uint32_t len = mmap->len;
	Console_Printf("During Map Reserved Base %x Len %x\r\n",address,len);

	
	uint32_t PDB_Index = (address>>22)&0x000003FF;
	uint32_t PT_Index = (address >>12)&0x000003FF;
	uint32_t POFFSET  = (address) & 0x00000FFF;
	uint32_t Count = len / 4096 ;


	Console_Printf("PDB_INDEX %x, PT_INDEX %x, POFFSET %x, Count %d \r\n",PDB_Index,PT_Index,POFFSET,Count);
	if(Count < 1024 ){
		MapReservedHelper(address,PDB_Index,PT_Index,Count);
	} else {
		//uint32_t i = Count / 1024;
		for(int i=0;i< Count / 1024 ; ++i){
			MapReservedHelper(address+0x1000*1024*i,PDB_Index,PT_Index,1024);
		}
	}

}

static void AppendFreeMemMap(multiboot_memory_map_t* mmap){
}



void MM_PAGE_Init(multiboot_info_t* mbd){
	uint32_t* PDB = MM_PAGE_GetPageDirectoryBaseAddr();
	for(int i=0;i<1024;++i){
		PDB[i]=0;
	}
	uint32_t address = 0;
	uint32_t* fpt = PDB+0x1000;
	for(int i=0;i<1024;++i){
		fpt[i] = address|3;
		address+=4096;
	}
	PDB[0] = fpt;
	//PDB[0] |= 3;

	//PDB[0x300] = fpt;
	//PDB[0x300] |= 3;

	++PageTableCount;

	for(multiboot_memory_map_t* mmap = mbd->mmap_addr;
		mmap < mbd->mmap_addr+ mbd->mmap_length;){
		if (mmap->addr < 0x100000){
			// Do Nothing
		} else {
			if((mmap -> type != MULTIBOOT_MEMORY_AVAILABLE )){
				MapReserved(mmap);
			} else {
				AppendFreeMemMap(mmap);
			}
		}
	
		mmap = (multiboot_memory_map_t* )((uint32_t)(mmap)+mmap->size + sizeof(uint32_t));
	}	   
	for(int i=0;i<1024;++i){
		if(PDB[i]){
			PDB[i]|=3;
		} else {
			PDB[i]|=2;
		}
	}
	//for(;;);

	__asm__ volatile("mov %0, %%cr3":: "b"(PDB));
	unsigned int cr0;
	__asm__ volatile("mov %%cr0, %0": "=b"(cr0));
	cr0 |= 0x80000000;
	__asm__ volatile("mov %0, %%cr0":: "b"(cr0));

	Inited = True;

	ISR_InstallHandler(14,MM_PAGE_FaultHandler);
	
}



void MM_PAGE_FaultHandler(struct ISR_Regs* reg){
	Console_Printf("During Page Fault Handler \r\n");
	__asm__ ("hlt;");
}
