#include "GDT.h"
#include "stdint.h"
struct GdtEntry{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} __attribute__((packed));

struct GdtPtr{
	uint16_t limit;
	uint32_t base;
}__attribute__((packed));

struct GdtEntry __gdt[3];
struct GdtPtr   __gp;
static void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
    /* Setup the descriptor base address */
    __gdt[num].base_low = (base & 0xFFFF);
    __gdt[num].base_middle = (base >> 16) & 0xFF;
    __gdt[num].base_high = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    __gdt[num].limit_low = (limit & 0xFFFF);
    __gdt[num].granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    __gdt[num].granularity |= (gran & 0xF0);
    __gdt[num].access = access;
}

void GDTInstall()
{
    /* Setup the GDT pointer and limit */
    __gp.limit = (sizeof(struct GdtEntry) * 3) - 1;
    __gp.base = &__gdt;

    /* Our NULL descriptor */
    gdt_set_gate(0, 0, 0, 0, 0);

    /* The second entry is our Code Segment. The base address
    *  is 0, the limit is 4GBytes, it uses 4KByte granularity,
    *  uses 32-bit opcodes, and is a Code Segment descriptor.
    *  Please check the table above in the tutorial in order
    *  to see exactly what each value means */
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    /* The third entry is our Data Segment. It's EXACTLY the
    *  same as our code segment, but the descriptor type in
    *  this entry's access byte says it's a Data Segment */
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    /* Flush out the old GDT and install the new changes! */
    gdt_flush();
}




