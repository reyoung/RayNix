#ifndef KERNEL_DRIVER_INPUT_KEYBOARD_H
#define KERNEL_DRIVER_INPUT_KEYBOARD_H
#include "stdint.h"

#define IO_KEY_CODE_IS_PRESS 0x80


uint8_t* IO_Keyboard_GetLayout();



#endif
