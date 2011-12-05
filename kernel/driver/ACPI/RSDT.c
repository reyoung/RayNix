#include "RSDT.h"
#include "RSDP.h"

ACPI_RSDT_Header* ACPI_RSDT_GetHeader(){
	RSDP_Descriptor_V10* desc = RSDP_GetDescriptor();
	return (ACPI_RSDT_Header*)(desc->RsdtAddress);	
}
