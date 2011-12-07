#include "kmalloc.h"
#include "stdint.h"
#include "../console.h"
#include "kheap.h"
struct KMallocNode{
	uint32_t prev;
	uint32_t next;
	uint32_t free:1;
	uint32_t length:31;
};
static void KMallocExpend(size_t sz){
	size_t extend_pages = sz/0x1000+1;
	size_t curEnd = MM_KHeap_CurrentHeapSize()*0x1000+KHEAP_BASE_ADDRESS;
	struct KMallocNode* root = (struct KMallocNode*)KHEAP_BASE_ADDRESS;
	MM_KHeap_Increase(extend_pages);

	struct KMallocNode* end = root;
	while(end->next) end = end->next;

	if(end->free){
		end->length += extend_pages * 0x1000;
	} else {
		struct KMallocNode* newEnd = (struct KMallocNode*)curEnd;
		newEnd->prev = end;
		newEnd->next = 0;
		newEnd->free = 1;
		newEnd->length = extend_pages*0x1000 - sizeof(struct KMallocNode);
		end->next = newEnd;
	}
	
}


void  MM_kmalloc_dump(){
	struct KMallocNode* p =(struct KMallocNode* )(KHEAP_BASE_ADDRESS);
	Console_Printf("During Kmalloc Dump \r\n");
	while(p!=0){
		
		Console_Printf("\tNode Addr %x, Prev %x, Next %x, IsFree %d, Len %d(0x%x)\r\n",
				p,p->prev,p->next,p->free,p->length,p->length	
				);


		p=p->next;
	}
	Console_Printf("Finish Kmalloc Dump \r\n");
}

static void* KMallocHelper(struct KMallocNode* pos, size_t sz){
	if(pos->length > sz + sizeof(struct KMallocNode)){ // 如果空闲长度大于需要的长度，加上Malloc头的长度
		uint32_t curAddr = (uint32_t)pos;
		uint32_t size =(uint32_t) sz;
		//Console_Printf("CurAddr %x \r\n",curAddr);
		uint32_t nextHeaderPos = curAddr + size + sizeof(struct KMallocNode);
		//Console_Printf("Next Header Pos %x \r\n",nextHeaderPos);
		uint32_t nextHeaderLen = pos->length - size - sizeof(struct KMallocNode);

		struct KMallocNode* n = (struct KMallocNode* ) (nextHeaderPos);
		n->prev = pos;
		n->next = pos->next;
		n->free = 1;
		n->length = nextHeaderLen;

		pos->next = n;
		pos->length = sz;
	}
	pos->free = 0; // 不free了
	uint32_t retv = (uint32_t ) pos + sizeof(struct KMallocNode);
	return (void*)retv;
}

void  MM_kmalloc_init(){
//	Console_Printf("Sizeof KMallocNode %d\r\n",sizeof(struct KMallocNode));
	uint32_t base = KHEAP_BASE_ADDRESS;
	uint32_t size = MM_KHeap_CurrentHeapSize()*0x1000;
	//uint32_t end  = size + KHEAP_BASE_ADDRESS; // Unused.
	struct KMallocNode* root =  (struct KMallocNode*)(base);
	root->prev = 0;
	root->next = 0;
	root->free = 1;
	root->length = size - sizeof(struct KMallocNode);

}

void* kmalloc(size_t sz){
	struct KMallocNode* root = (struct KMallocNode* )(KHEAP_BASE_ADDRESS);
	struct KMallocNode* p = root;
	while(p!=0){
		if( p->free && p->length >= sz){
		//	Console_Printf("P_ADDRESS %x\n",p);
			return KMallocHelper(p,sz);
		}
		p=p->next;
	}
	KMallocExpend(sz);
	return kmalloc(sz);
}
void  kfree(void* mem){
}
