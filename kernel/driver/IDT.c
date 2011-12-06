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
extern void ___isr6();
extern void ___isr7();
extern void ___isr8();
extern void ___isr9();
extern void ___isr10();
extern void ___isr11();
extern void ___isr12();
extern void ___isr13();
extern void ___isr14();
extern void ___isr15();
extern void ___isr16();
extern void ___isr17();
extern void ___isr18();
extern void ___isr19();
extern void ___isr20();
extern void ___isr21();
extern void ___isr22();
extern void ___isr23();
extern void ___isr24();
extern void ___isr25();
extern void ___isr26();
extern void ___isr27();
extern void ___isr28();
extern void ___isr29();
extern void ___isr30();
extern void ___isr31();

extern void ___irq0();
extern void ___irq1();

void IDTInstall(){
	// because idts is static data, don't need to memset to zero.
	//memset(idts,0,sizeof(struct IDTEntry)*256);
#define IDT_SET_GATE(num)\
	idt_set_gate(num,(uint32_t)___isr##num,0x08,0x8E)

	IDT_SET_GATE(0);
	IDT_SET_GATE(1);
	IDT_SET_GATE(2);
	IDT_SET_GATE(3);
	IDT_SET_GATE(4);
	IDT_SET_GATE(5);
	IDT_SET_GATE(6);
	IDT_SET_GATE(7);
	IDT_SET_GATE(8);
	IDT_SET_GATE(9);
	IDT_SET_GATE(10);
	IDT_SET_GATE(11);
	IDT_SET_GATE(12);
	IDT_SET_GATE(13);
	IDT_SET_GATE(14);
	IDT_SET_GATE(15);
	IDT_SET_GATE(16);
	IDT_SET_GATE(17);
	IDT_SET_GATE(18);
	IDT_SET_GATE(19);
	IDT_SET_GATE(20);
	IDT_SET_GATE(21);
	IDT_SET_GATE(22);
	IDT_SET_GATE(23);
	IDT_SET_GATE(24);
	IDT_SET_GATE(25);
	IDT_SET_GATE(26);
	IDT_SET_GATE(27);
	IDT_SET_GATE(28);
	IDT_SET_GATE(29);
	IDT_SET_GATE(30);
	IDT_SET_GATE(31);
#undef IDT_SET_GATE
	idt_set_gate(32,(uint32_t ) ___irq0,0x08,0x8E);
	idt_set_gate(33,(uint32_t) ___irq1,0x08,0x8E);	


	lidt(&idts,(sizeof (struct IDTEntry) * 256) - 1);
}


