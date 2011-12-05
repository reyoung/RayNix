#ifndef KERNEL_DRIVER_GDT_H
#define KERNEL_DRIVER_GDT_H

// The GDT Knowledge Reference from 
//	1.http://wiki.osdev.org/GDT_Tutorial
//	2.http://wiki.osdev.org/GDT
// Implenment Reference from 
// 	http://www.osdever.net/bkerndev/Docs/gdt.htm

// Use GDT_ASM.S to implement this.
extern void gdt_flush();

// Init Method, To setup gdt.
void GDTInstall();

#endif
