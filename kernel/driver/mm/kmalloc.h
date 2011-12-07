#ifndef KERNEL_DRIVER_MM_KMALLOC_H
#define KERNEL_DRIVER_MM_KMALLOC_H
#include "stddef.h"

void* kmalloc(size_t sz);
void  kfree(void* mem);

#endif
