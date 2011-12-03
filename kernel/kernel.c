#include "atol.h"
#include "multiboot.h"
#include "driver/console.h"

void kmain( multiboot_info_t* mbd, unsigned int magic )
{
   if ( magic != 0x2BADB002 )
   {
      /* Something went not according to specs. Print an error */
      /* message and halt, but do *not* rely on the multiboot */
      /* data structure. */
   }
   Console_Init();
   Console_PutCharWithColor('H',0xE7);
}
