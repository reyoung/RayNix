#include "kheap.h"
#include "Page.h"
static size_t HeapSize = 0;
size_t MM_KHeap_CurrentHeapSize(){
	return HeapSize;
}

void MM_KHeap_Increase(size_t sz){
	for(size_t i=0;i<sz;++i){
		void* heapBtmAddr = KHEAP_BASE_ADDRESS + HeapSize*0x1000;
		MM_PAGE_AllocPage(heapBtmAddr);
		++HeapSize;
	}
}

void MM_KHeap_Decrease(size_t sz){
	for(size_t i=0;i<sz;++i){
		void* heapBtmAddr = KHEAP_BASE_ADDRESS + HeapSize*0x1000 -1;
		MM_PAGE_FreePage(heapBtmAddr);
		--HeapSize;
	}
}


