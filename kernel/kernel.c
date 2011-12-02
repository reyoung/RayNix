void ClearScreen(int n,char color){
	int i;
	unsigned char *videoram = (unsigned char *) 0xb8000;
	for(i=0;i<2*n;++i){
		videoram[i*2]=' ';
		videoram[i*2+1]=color;
	}
}


void kmain( void* mbd, unsigned int magic )
{
   if ( magic != 0x2BADB002 )
   {
      /* Something went not according to specs. Print an error */
      /* message and halt, but do *not* rely on the multiboot */
      /* data structure. */
   }
 
   /* You could either use multiboot.h */
   /* (http://www.gnu.org/software/grub/manual/multiboot/multiboot.html#multiboot_002eh) */
   /* or do your offsets yourself. The following is merely an example. */ 
   //char * boot_loader_name =(char*) ((long*)mbd)[16];
 
   /* Print a letter to screen to see everything is working: */
   unsigned char *videoram = (unsigned char *) 0xb8000;
   ClearScreen(80*25,0x1E);
   videoram[0] = 'H'; /* character 'A' */
   videoram[2] = 'E'; /* character 'A' */
   videoram[4] = 'L'; /* character 'A' */
   videoram[6] = 'L'; /* character 'A' */
   videoram[8] = 'O'; /* character 'A' */
   videoram[10] = '!'; /* character 'A' */
}