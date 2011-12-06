#include "atol.h"
#include "multiboot.h"
#include "driver/console.h"
#include "sys/info.h"
#include "driver/ACPI/RSDP.h"
#include "driver/ACPI/RSDT.h"
#include "driver/ACPI/FADT.h"
#include "driver/GDT.h"
#include "driver/IDT.h"
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
   Console_Init();

   Console_SetDefaultColor(0x1E);
   Console_Clear();
   Console_Printf("===============%s Ver %s.%s==============\r\n",OS_NAME,OS_MAJOR_VERSION,OS_MINOR_VERSION);
   if(mbd->flags&MULTIBOOT_INFO_MEMORY){
   	Console_Printf("Total Mem %dK, Uppder Mem %dk, Lower Mem %dk\r\n",mbd->mem_lower+mbd->mem_upper,mbd->mem_upper,mbd->mem_lower);
   }
   Console_Printf("System RSDP Version %d, ",RSDP_GetVersion());
   RSDP_Descriptor_V10* desc = RSDP_GetDescriptor();
   Console_Printf("OEMID %s,Rsdt Address %d,Is Valid %d.\r\n",desc->OEMID,desc->RsdtAddress,RSDP_IsValid()?1:0);
   ACPI_RSDT_Header* header = ACPI_RSDT_GetHeader();
   Console_Printf("System RSDT, IsValid %d, Signature %s, OEMID %s,\r\n",ACPI_RSDT_IsValid(),header->Signature,header->OEMID);
   ACPI_FADT* fadt = ACPI_FADT_GetInstance();
   Console_Printf("System FADT IsValid %d, Len %u, PPMP %d\r\n",ACPI_FADT_IsValid(),fadt->header.Length,(int)fadt->PreferredPowerManagementProfile);
   if (!ACPI_IsEnabled()){
   	Console_Printf("Enabling ACPI.......%d\r\n",ACPI_Enable());
   }
}
