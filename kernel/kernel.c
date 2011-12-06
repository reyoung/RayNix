#include "atol.h"
#include "multiboot.h"
#include "driver/console.h"
#include "sys/info.h"
#include "driver/ACPI/RSDP.h"
#include "driver/ACPI/RSDT.h"
#include "driver/ACPI/FADT.h"
#include "driver/GDT.h"
#include "driver/IDT.h"
#include "driver/IRQ.h"
#include "driver/CMOS.h"
#include "driver/mm/Page.h"


void TimerHandler(struct ISR_Regs* regs){
	//Console_Printf("Handlling Timer IRQ \r\n");
}

char Buffer[256];
extern uint32_t ___KernelEnd;


void kmain( multiboot_info_t* mbd, unsigned int magic )
{
   if ( magic != 0x2BADB002 )
   {
      /* Something went not according to specs. Print an error */
      /* message and halt, but do *not* rely on the multiboot */
      /* data structure. */
   }
   GDTInstall();
   IDTInstall();
   IRQ_Init();
   MM_PAGE_Init();	


   Console_Init();
   
   IRQ_UninstallHandler(0);
   IRQ_InstallHandler(0,TimerHandler);
   Console_SetDefaultColor(0x1E);
   Console_Clear();


   Console_Printf("========================%s Ver %s.%s==============",OS_NAME,OS_MAJOR_VERSION,OS_MINOR_VERSION);
   CMOS_DateTime dt;
   CMOS_GetCurrentDateTime(&dt);
   Console_Printf("%d-%d-%d %d:%d:%d\r\n",(int)dt.Month,(int)dt.Day,(int)dt.Year,(int)dt.Hour,(int)dt.Min,(int)dt.Second);

   Console_Printf("Kernel End At %x, PDB %x\r\n",&___KernelEnd,MM_PAGE_GetPageDirectoryBaseAddr());


   if(mbd->flags&MULTIBOOT_INFO_MEMORY){
   	Console_Printf("Total Mem %dK, Uppder Mem %dk, Lower Mem %dk\r\n",mbd->mem_lower+mbd->mem_upper,mbd->mem_upper,mbd->mem_lower);
   }
   Console_Printf("System RSDP Version %d, ",RSDP_GetVersion());
   RSDP_Descriptor_V10* desc = RSDP_GetDescriptor();
   Console_Printf("OEMID %s,Rsdt Address %x,Is Valid %d.\r\n",desc->OEMID,desc->RsdtAddress,RSDP_IsValid()?1:0);
   int* ptr = 4194305;
   Console_Printf("I wanna Page Fault! %d\r\n",*ptr);
/*
	//! For PageFalut, Need to init APCI Before Page.
   ACPI_RSDT_Header* header = ACPI_RSDT_GetHeader();
   Console_Printf("System RSDT, IsValid %d, Signature %s, OEMID %s,\r\n",ACPI_RSDT_IsValid(),header->Signature,header->OEMID);
   ACPI_FADT* fadt = ACPI_FADT_GetInstance();
   Console_Printf("System FADT IsValid %d, Len %u, PPMP %d\r\n",ACPI_FADT_IsValid(),fadt->header.Length,(int)fadt->PreferredPowerManagementProfile);
   if (!ACPI_IsEnabled()){
   	Console_Printf("Enabling ACPI.......%d\r\n",ACPI_Enable());
   }
*/
   for(;;);
}
