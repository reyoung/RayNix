#include "atol.h"
#include "multiboot.h"
static char BUFFER[512];
void ClearScreen(int n,char color){
	int i;
	unsigned char *videoram = (unsigned char *) 0xb8000;
	for(i=0;i<2*n;++i){
		videoram[i*2]=' ';
		videoram[i*2+1]=color;
	}
}


void kmain( multiboot_info_t* mbd, unsigned int magic )
{
   if ( magic != 0x2BADB002 )
   {
      /* Something went not according to specs. Print an error */
      /* message and halt, but do *not* rely on the multiboot */
      /* data structure. */
   }
   unsigned char *videoram = (unsigned char *) 0xb8000;
   ClearScreen(80*25,0x1E);
   itoa(mbd->mmap_length,BUFFER,10);
   
   
   videoram[0] = BUFFER[0]; /* character 'A' */
   videoram[2] = BUFFER[1]; /* character 'A' */
   videoram[4] = BUFFER[2]; /* character 'A' */
   videoram[6] = BUFFER[3]; /* character 'A' */
   videoram[8] = 'O'; /* character 'A' */
   videoram[10] = '!'; /* character 'A' */
}