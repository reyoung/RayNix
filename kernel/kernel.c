#include "atol.h"
#include "multiboot.h"
#include "driver/console.h"
#include "sys/info.h"
#include "driver/ACPI/RSDP.h"
#include "driver/ACPI/RSDT.h"
#include "driver/ACPI/FADT.h"
#include "driver/ACPI/DSDT.h"
#include "driver/GDT.h"
#include "driver/IDT.h"
#include "driver/IRQ.h"
#include "driver/CMOS.h"
#include "driver/mm/Page.h"
#include "driver/mm/kheap.h"
#include "driver/cpuid.h"

void KeyboardHandler(uint8_t sc, uint32_t kc){
	uint8_t ch = kc;
	Console_Printf("Key Pressed, Scancode %d, Keycode %x, Char %c \r\n",(int)sc,kc,ch);
}

char Buffer[256];
extern uint32_t ___KernelEnd;

void kmain( multiboot_info_t* mbd, unsigned int magic )
{
   if ( magic != 0x2BADB002 )
   {
     int FAKE = 0;
     FAKE/=0;	// To make a exception exit the kernel.
   }
   GDTInstall();
   IDTInstall();
   IRQ_Init();
    

   
   Console_Init();

   Console_SetDefaultColor(0x1E);
   Console_Clear();

   MM_PAGE_Init(mbd);

   MM_kmalloc_init();
   Timer_Init();
   IO_Keyboard_Init();
   IO_Keyboard_AppendListener(KeyboardHandler);


   Console_Printf("========================%s Ver %s.%s==============",OS_NAME,OS_MAJOR_VERSION,OS_MINOR_VERSION);
   CMOS_DateTime dt;
   CMOS_GetCurrentDateTime(&dt);
   Console_Printf("%d-%d-%d %d:%d:%d\r\n",(int)dt.Month,(int)dt.Day,(int)dt.Year,(int)dt.Hour,(int)dt.Min,(int)dt.Second);

   Timer_Sleep(1000);

   Console_Printf("Is CPUID Supported? %d\r\n",CPUID_IsSupported());
   if(CPUID_IsSupported()){
   	CPUID_GetVendorString(Buffer);
   	Console_Printf(" CPUID Vendor String %s, CPU Feature %x. \r\n",Buffer,CPUID_GetFeature());
   }
/*
   for(multiboot_memory_map_t* mmap = mbd->mmap_addr;
		mmap < mbd->mmap_addr+ mbd->mmap_length;
      ){
   	Console_Printf("Mem Map From %x Length %x Size %x Flags %x \r\n", (int)mmap->addr, (int)mmap->len, mmap->size, mmap->type ) ;
	mmap = (multiboot_memory_map_t* )((uint32_t)(mmap)+mmap->size + sizeof(uint32_t));
   }
*/

   if(mbd->flags&MULTIBOOT_INFO_MEMORY){
   	Console_Printf("Total Mem %dK, Uppder Mem %dk, Lower Mem %dk\r\n",mbd->mem_lower+mbd->mem_upper,mbd->mem_upper,mbd->mem_lower);
   }
   Console_Printf("System RSDP Version %d, ",RSDP_GetVersion());
   RSDP_Descriptor_V10* desc = RSDP_GetDescriptor();
   Console_Printf("OEMID %s,Rsdt Address %x,Is Valid %d.\r\n",desc->OEMID,desc->RsdtAddress,RSDP_IsValid()?1:0);

   ACPI_RSDT_Header* header = ACPI_RSDT_GetHeader();
   Console_Printf("System RSDT, IsValid %d, Signature %s, OEMID %s,\r\n",ACPI_RSDT_IsValid(),header->Signature,header->OEMID);
   ACPI_FADT* fadt = ACPI_FADT_GetInstance();
   Console_Printf("System FADT IsValid %d, Len %u, PPMP %d, PM1ACNT %x, PM1BCNT %x \r\n",ACPI_FADT_IsValid(),fadt->header.Length,(int)fadt->PreferredPowerManagementProfile,fadt->PM1aControlBlock,fadt->PM1bControlBlock);

   Console_Printf("System DSDT IsValid %d S5 Object Address %x, SLP_TYPa %x,\r\n",ACPI_DSDT_IsValid(),(int)ACPI_DSDT_GetS5Object(),
		   ACPI_DSDT_S5_Get_SLP_TYPa());

//   Console_Clear();
//   ACPI_DSDT_Dump();
   
   while (!ACPI_IsEnabled()){
   	Console_Printf("Enabling ACPI.......%d\r\n",ACPI_Enable());
	Timer_Sleep(1000);
	Console_Printf("Is ACPI Enabled? %d\r\n",ACPI_IsEnabled());
   }
   int Timer = 5;
   Console_Printf("All Things Done. \r\n");
   for(;;){
   	Console_Printf("Shutdown In %d Second\r\n",Timer--);
	Timer_Sleep(1000);
	if(Timer==0){
		ACPI_Shutdown();
		for(;;);
	}
   }
}
