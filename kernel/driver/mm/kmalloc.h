#ifndef KERNEL_DRIVER_MM_KMALLOC_H
#define KERNEL_DRIVER_MM_KMALLOC_H
#include "stddef.h"

void  MM_kmalloc_init();

void* kmalloc(size_t sz);

void  kfree(void* mem);

void  MM_kmalloc_dump();

#endif
