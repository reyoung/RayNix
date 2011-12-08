#include "Keyboard.h"
#include "../mm/kmalloc.h"
#include "../IRQ.h"
#include "../InlineASM.h"
static uint32_t KeyFlag = 0;

typedef void (*CallbackType) (uint8_t , uint32_t);

typedef struct CallbackListNode{
	CallbackType Func;
	struct CallbackListNode* Next;
};

static struct CallbackListNode* ListRoot = 0;

static uint32_t kbdus[128]={
	0,IO_KEY_CODE_ESCAPE,'1','2','3','4','5','6','7','8','9','0',
	'-','=','\b','\t','q','w','e','r','t','y','u',
	'i','o','p','[',']','\n',
	IO_KEY_CODE_CONTROL,'a','s','d','f','g','h','j',
	'k','l',';','\'','`',IO_KEY_CODE_LSHIFT,'\\','z',
	'x','c','v','b','n','m',',','.','/',IO_KEY_CODE_RSHIFT,'*',
	IO_KEY_CODE_ALT,' ',IO_KEY_CODE_CAPSLOCK,IO_KEY_CODE_F1,
	IO_KEY_CODE_F2,IO_KEY_CODE_F3,IO_KEY_CODE_F4,IO_KEY_CODE_F5,
	IO_KEY_CODE_F6,IO_KEY_CODE_F7,IO_KEY_CODE_F8,IO_KEY_CODE_F9,
	IO_KEY_CODE_F10,IO_KEY_CODE_NUMLOCK,IO_KEY_CODE_SCROLLLOCK,
	IO_KEY_CODE_HOME,IO_KEY_CODE_UP,IO_KEY_CODE_PAGEUP,'-',
	iO_KEY_CODE_LEFT,0,IO_KEY_CODE_RIGHT,'+',IO_KEY_CODE_END,
	IO_KEY_CODE_DOWN,IO_KEY_CODE_PAGEDOWN,IO_KEY_CODE_INSERT,
	IO_KEY_CODE_DELETE,0,0,0,IO_KEY_CODE_F11,IO_KEY_CODE_F12,
};

static void keyboard_handler(struct ISR_Regs* r){
	uint8_t sc = inb(0x60);
	uint32_t kc = kbdus[sc&0x7F];

	if(sc&0x80){
		if(kc==IO_KEY_CODE_CONTROL){
			KeyFlag &= (~IO_KEY_CODE_CONTROL);
		} else if(kc==IO_KEY_CODE_LSHIFT){
			KeyFlag &= (~IO_KEY_CODE_LSHIFT);
		} else if(kc==IO_KEY_CODE_ALT){
			KeyFlag &= (~IO_KEY_CODE_ALT);
		} else if(kc==IO_KEY_CODE_CAPSLOCK){
			if(KeyFlag & IO_KEY_CODE_CAPSLOCK){
				KeyFlag &= (~IO_KEY_CODE_CAPSLOCK);
			} else {
				KeyFlag |= IO_KEY_CODE_CAPSLOCK;
			}
		} else if(kc==IO_KEY_CODE_NUMLOCK){
			if(KeyFlag & IO_KEY_CODE_NUMLOCK){
				KeyFlag &= (~IO_KEY_CODE_NUMLOCK);
			} else {
				KeyFlag |= IO_KEY_CODE_NUMLOCK;
			}
		} else if(kc==IO_KEY_CODE_SCROLLLOCK){
			if(KeyFlag & IO_KEY_CODE_SCROLLLOCK){
				KeyFlag &= (~IO_KEY_CODE_SCROLLLOCK);
			} else {
				KeyFlag |= IO_KEY_CODE_SCROLLLOCK;
			}
		}
		kc|=IO_KEY_CODE_IS_PRESS;
	} else {
		if(kc==IO_KEY_CODE_CONTROL){
			KeyFlag |= IO_KEY_CODE_CONTROL;
		} else if(kc==IO_KEY_CODE_LSHIFT){
			KeyFlag |= IO_KEY_CODE_LSHIFT;
		} else if(kc==IO_KEY_CODE_ALT){
			KeyFlag |= IO_KEY_CODE_ALT;
		}
	}
	kc|=KeyFlag;


	struct CallbackListNode* p = ListRoot;
	while(p){
		p->Func(sc,kc);
		p=p->Next;
	}
};


void IO_Keyboard_Init(){
	IRQ_InstallHandler(1,keyboard_handler);
}




uint32_t* IO_Keyboard_GetLayout(){
	return kbdus;
}


void IO_Keyboard_AppendListener(void  (*func)(uint8_t scancode, uint32_t translated_code)){
	struct CallbackListNode* newNode = kmalloc(sizeof(struct CallbackListNode));
	newNode->Next = ListRoot;
	newNode->Func = func;
	ListRoot = newNode;
}

boolean IO_Keyboard_RemoveListener(void (*func)(uint8_t scancode, uint32_t translated_code)){
	struct CallbackListNode* p = ListRoot;
	struct CallbackListNode* prep = 0;
	while(p){
		if(p->Func == func){
			if(prep == 0){
				ListRoot = p->Next;
				kfree(p);
			} else {
				prep->Next = p->Next;
				kfree(p);
			}
			return True;
		}
		prep = p;
		p = p->Next;
	}
	return False;
}

