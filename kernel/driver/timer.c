#include "timer.h"
#include "../sys/info.h"
#include "InlineASM.h"
#include "isr.h"
#include "mm/kmalloc.h"
#include "console.h"
#include "irq.h"
#define X86_FREQUENCY 1193180

typedef void(* Listener) (struct ISR_Regs* );

struct LNode{
	struct LNode* Next;
	Listener Data;
};

static struct LNode* m_root = 0;

static uint32_t Ticker = 0;

static void __sleep_listener(struct ISR_Regs* reg){
//	Console_Printf("In Sleep Listener \r\n");
	++ Ticker;
}


static void tmain(struct ISR_Regs* regs){
	struct LNode* p = m_root;
//	Console_Printf("In Sleep Listener \r\n");
	while(p){
		p->Data(regs);
		p=p->Next;
	}
}


void Timer_Sleep(int ms){
	if(ms<10)
		return ;
	else {
		uint32_t etick = Ticker + ms/OS_TICK_TIME;
		while(Ticker<etick){
			__asm__("nop");
		}
	}
}

void Timer_AppendOnTickListener(void(*listener)(struct ISR_Regs*)){
	struct LNode* node = (struct LNode*)kmalloc(sizeof(struct LNode));
	node->Next = m_root;
	node->Data = listener;
	m_root = node;
}

boolean Timer_RemoveOnTickListener(void(*listener)(struct ISR_Regs*)){
	struct LNode* p = m_root;
	struct LNode* prev = 0;
	while(p){
		if(p->Data == listener){
			if(prev){
				prev->Next = p->Next;
			} else {
				m_root = p->Next;
			}
			kfree(p);
			return True;
		}
		p=p->Next;
	}
	return False;
}

void Timer_Init(){

	int div = X86_FREQUENCY / OS_TICK_HZ;
	outb(0x43,0x36);
	outb(0x40,div&0xFF);
	outb(0x40,div>>8);

	IRQ_InstallHandler(0,tmain);
	Timer_AppendOnTickListener(__sleep_listener);
}


