#include "Page.h"
#include "../console.h"


#define PAGE_FAULT_TYPE_ISPROTECTION 0x01


extern uint32_t ___KernelEnd;
static int PageTableCount = 0;
static boolean Inited = False;


static uint8_t Page_Bitmap_Table[128*1024]={0xFF};

#define BIT_SETTED(v,i)\
	(v&(1<<i))

#define SET_BIT(v,i)\
	(v)|=(1<<(i))

#define UNSET_BIT(v,i)\
	(v)&=(~(1<<(i)))

static inline void MakePhysicalAddrUsed(void* addr){
	uint32_t page_no = (uint32_t)addr /4096;
	uint32_t i = page_no /8;
	uint32_t j = page_no %8;
	SET_BIT(Page_Bitmap_Table[i],j);
}
static inline void FreePhysicalAddr(void* addr){
	uint32_t page_no = (uint32_t) addr / 4096;
	uint32_t i = page_no/8;
	uint32_t j = page_no%8;
	UNSET_BIT(Page_Bitmap_Table[i],j);
}

static void* GetAFreePhysicalAddr(){
	for(int i=0; i<128*1024;++i){
		if(Page_Bitmap_Table[i]!=0xFF){ // 完全占用
			//Console_Printf("i=%d\r\n",i);
			uint8_t temp = Page_Bitmap_Table[i];
			int j;
			temp =~temp;
			for(j=0;j<8;++j){
				if( temp&(1<<j)){
					break;
				}
			}
			return (void*)( i*8*4096 + j*4096);
		}
	}
	return (void*)0;
}

static void* AllocAFreePhysicalAddr(){
	void* result = GetAFreePhysicalAddr();
	MakePhysicalAddrUsed(result);
	return result;
}



static inline boolean IsMemUsed(void* addr){
	uint32_t t = (uint32_t) addr / 0x1000;
	return BIT_SETTED(Page_Bitmap_Table[t/8],t%8)!=0;
}

uint32_t* MM_PAGE_GetPageDirectoryBaseAddr(){
	uint32_t end = (uint32_t)&___KernelEnd;
	uint32_t page_aligned_end = (end&0xFFFFF000)+0x1000;
	return (uint32_t*) page_aligned_end;
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
		PDB[pdbindex]=(uint32_t)fp;
		//PDB[PDB_Index]|=3;
	} else {
		fp = (uint32_t*)PDB[pdbindex];
	}
	for(uint32_t i = 0; i< count ;++i ){
		fp[ptindex+i] = address|3;
		address+= 0x1000;
	}
}


static void MapReserved(multiboot_memory_map_t* mmap ){
	uint32_t address = mmap->addr;
	uint32_t len = mmap->len;
	//Console_Printf("During Map Reserved Base %x Len %x\r\n",address,len);
	
	uint32_t PDB_Index = (address>>22)&0x000003FF;
	uint32_t PT_Index = (address >>12)&0x000003FF;
	uint32_t POFFSET  = (address) & 0x00000FFF;
	uint32_t Count = len / 4096 ;


	//Console_Printf("PDB_INDEX %x, PT_INDEX %x, POFFSET %x, Count %d \r\n",PDB_Index,PT_Index,POFFSET,Count);
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
	uint32_t address = mmap->addr;
	uint32_t len = mmap->len;
	if(address < 0x00400000){ // < 4 MB
		uint32_t del = 0x00400000 - address;
		if(len < del ) {
			return ;
		} else {
			len -= del;
			address = 0x00400000;
		}
	}
	address /= 0x1000;
	len     /= 0x1000;
	//Console_Printf("AppendFreeMemMap Addr %x,Len %x \r\n",address,len);
	for(uint32_t i =0; i<len; ++i){
		if( address%8==0 && len - i >=8){
			
		}
		uint32_t index = address/8;
		uint32_t bitpos = address%8;
		Page_Bitmap_Table[index] &= ~(1<<bitpos);
		++address;
	}
	//Console_Printf("Addr 0x400 %x\r\n",(int)Page_Bitmap_Table[0x7F]);
}



void MM_PAGE_Init(multiboot_info_t* mbd){
	uint32_t* PDB = MM_PAGE_GetPageDirectoryBaseAddr();

	for(int i=0;i<128*1024;++i){
		Page_Bitmap_Table[i]=0xFF;
	}


	for(int i=0;i<1024;++i){
		PDB[i]=0;
	}
	uint32_t address = 0;
	uint32_t* fpt = PDB+0x1000;
	for(int i=0;i<1024;++i){
		fpt[i] = address|3;
		address+=4096;
	}
	PDB[0] =(uint32_t) fpt;
	//PDB[0] |= 3;

	//PDB[0x300] = fpt;
	//PDB[0x300] |= 3;

	++PageTableCount;

	for(multiboot_memory_map_t* mmap =(multiboot_memory_map_t*) mbd->mmap_addr;
		mmap <(multiboot_memory_map_t*)(mbd->mmap_addr+ mbd->mmap_length);){
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
/*
	void* testAddr  = AllocAFreePhysicalAddr();
	void* t2 = AllocAFreePhysicalAddr();
	Console_Printf("A Alloced Free Mem addr  %x,%x, Is it used? %d\r\n",testAddr,t2,IsMemUsed(testAddr));
	FreePhysicalAddr(testAddr);
	FreePhysicalAddr(t2);
	Console_Printf("Is TestAddr And T2 Freed? %d %d \r\n",!IsMemUsed(testAddr),!IsMemUsed(t2));

	for(;;);
*/
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
	
	uint8_t ErrCode= reg->err_code;
	if(ErrCode&PAGE_FAULT_TYPE_ISPROTECTION){
		Console_Printf("Protection Page Fault, Hlt!\r\n");
		__asm__("hlt;");
	} else {
		uint32_t addr=0;
		__asm__ ("mov %%cr2,%0":"=a"(addr));
		uint32_t PDB_Index = (addr>>22)&0x3FF;
		uint32_t PT_Index = (addr>>12)&0x3FF;
		uint32_t used_addr = AllocAFreePhysicalAddr();
		uint32_t* PDB = MM_PAGE_GetPageDirectoryBaseAddr();
		if(PDB[PDB_Index]&1){
			uint32_t* pt = PDB[PDB_Index]&0xFFFFF000;
			pt[PT_Index] = used_addr;
			pt[PT_Index] |= 3;
		} else {
			++PageTableCount;
			uint32_t* pt = PDB+ 0x1000 * PageTableCount;
			for(uint32_t i =0;i<1024;++i){
				pt[i]=0;
				pt[i]|=2;
			}
			
			pt[PT_Index] = used_addr;
			pt[PT_Index] |= 3;
			PDB[PDB_Index] = pt;
			PDB[PDB_Index] |=3;
			
		}
	}
		
	//__asm__ ("hlt;");
}
