#ifndef KERNEL_DRIVER_MM_KHEAP_H
#define KERNEL_DRIVER_MM_KHEAP_H
#include "stddef.h"
#define KHEAP_BASE_ADDRESS 0x80000000
#define MM_KHeap_Init()\
	MM_KHeap_Increase(1)

// All Heap size unit is 4k, same as page size;

size_t MM_KHeap_CurrentHeapSize();

void MM_KHeap_Increase(size_t sz);

void MM_KHeap_Decrease(size_t sz);

#endif
