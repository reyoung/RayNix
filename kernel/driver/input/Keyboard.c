#include "Keyboard.h"
#include "keyboard.h"

static uint8_t kbdus[128]={
	0,27,'1','2','3','4','5','6','7','8','9','0',
	'-','=',
};
uint8_t* IO_Keyboard_GetLayout(){
	return kbdus;
}




