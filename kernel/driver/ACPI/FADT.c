#include "FADT.h"

#define ACPI_FADT_SIGNATURE "FACP"


ACPI_FADT* ACPI_FADT_GetInstance(){
	return ACPI_RSDT_GetEntry(ACPI_FADT_SIGNATURE);
}

boolean ACPI_FADT_IsValid(){
	ACPI_FADT* fadt = ACPI_FADT_GetInstance();
	if(fadt==0){
		return False;
	} else {
		uint32_t l = fadt->header.Length;
		uint8_t cksum = 0;
		char*  p = (char* )fadt;
		for(uint32_t i =0;i<l;++i){
			cksum+=p[i];
		}
		return cksum==0;
	}
}

