#include "IDT.h"
#include "GDT.h"
#include "stdint.h"
static inline
void lidt( void * base, unsigned int size )
{
    unsigned int i[2];
 
    i[0] = size << 16;
    i[1] = (unsigned int)base;
    __asm( "lidt (%0)"
         : : "p"(((char *) i)+2) );
}

struct IDTEntry{
	uint16_t base_lo;
	uint16_t sel;	// GDT selector
	uint8_t always0;
	uint8_t flags;
	uint16_t base_hi;
} __attribute__((packed));

static struct IDTEntry idts[256];
static void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
	// TODO Complete IDT_SET_GATE
}
void IDTInstall(){
	// because idts is static data, don't need to memset to zero.
	//memset(idts,0,sizeof(struct IDTEntry)*256);
	
	lidt(&idts,(sizeof (struct IDTEntry) * 256) - 1);
}


