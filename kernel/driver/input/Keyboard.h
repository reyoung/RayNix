#ifndef KERNEL_DRIVER_INPUT_KEYBOARD_H
#define KERNEL_DRIVER_INPUT_KEYBOARD_H
#include "stdint.h"

#define IO_KEY_CODE_UNDEFINE 0

#define IO_KEY_CODE_IS_PRESS 0x100
#define IO_KEY_CODE_CONTROL  0x200
#define IO_KEY_CODE_LSHIFT   0x400
#define IO_KEY_CODE_RSHIFT   0x800
#define IO_KEY_CODE_ALT      0x1000
#define IO_KEY_CODE_CAPSLOCK 0x2000
#define IO_KEY_CODE_NUMLOCK  0x4000
#define IO_KEY_CODE_SCROLLLOCK 0x8000

#define IO_KEY_CODE_F1	     0x80
#define IO_KEY_CODE_F2	     0x81
#define IO_KEY_CODE_F3	     0x82
#define IO_KEY_CODE_F4	     0x83
#define IO_KEY_CODE_F5	     0x84
#define IO_KEY_CODE_F6       0x85
#define IO_KEY_CODE_F7       0x86
#define IO_KEY_CODE_F8	     0x86
#define IO_KEY_CODE_F9       0x87
#define IO_KEY_CODE_F10      0x88
#define IO_KEY_CODE_F11      0x89
#define IO_KEY_CODE_F12      0x8A
#define IO_KEY_CODE_HOME     0x8B
#define iO_KEY_CODE_LEFT     0x8C
#define IO_KEY_CODE_RIGHT    0x8D
#define IO_KEY_CODE_DOWN     0x8E
#define IO_KEY_CODE_UP       0x8F
#define IO_KEY_CODE_PAGEUP   0x90
#define IO_KEY_CODE_END	     0x91
#define IO_KEY_CODE_PAGEDOWN 0x92
#define IO_KEY_CODE_INSERT   0x93
#define IO_KEY_CODE_DELETE   0x94

#define IO_KEY_CODE_ESCAPE   27

uint32_t* IO_Keyboard_GetLayout();

void IO_Keyboard_Init();

void IO_Keyboard_AppendListener(void  (*func)(uint8_t scancode, uint32_t translated_code));

boolean IO_Keyboard_RemoveListener(void (*func)(uint8_t scancode, uint32_t translated_code));


#endif
