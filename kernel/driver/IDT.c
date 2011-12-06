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
static void idt_set_gate(unsigned char num, uint32_t base, unsigned short sel, unsigned char flags)
{
	idts[num].base_lo = (base&0xffff);
	idts[num].base_hi = (base>>16)&0xffff;
	idts[num].sel = sel;
	idts[num].flags = flags;
	idts[num].always0 = 0;
}

extern void ___isr0();
extern void ___isr1();
extern void ___isr2();
extern void ___isr3();
extern void ___isr4();
extern void ___isr5();
void IDTInstall(){
	// because idts is static data, don't need to memset to zero.
	//memset(idts,0,sizeof(struct IDTEntry)*256);
#define IDE_SET_GATE(num)\
	idt_set_gate(num,(uint32_t)___isr##num,0x08,0x8E)

	IDE_SET_GATE(0);
	IDE_SET_GATE(1);
	IDE_SET_GATE(2);
	IDE_SET_GATE(3);
	IDE_SET_GATE(4);
	IDE_SET_GATE(5);


#undef IDE_SET_GATE


	lidt(&idts,(sizeof (struct IDTEntry) * 256) - 1);
}

