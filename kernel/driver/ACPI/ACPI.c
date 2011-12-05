#include "ACPI.h"
#include "FADT.h"
#include "../io.h"
boolean ACPI_IsEnabled(){
	ACPI_FADT* fadt = ACPI_FADT_GetInstance();
	if(ACPI_FADT_IsValid()){
		return fadt->SMI_CommandPort==0 && fadt->AcpiEnable==0 && fadt->AcpiDisable==0;
	} else {
		return False;
	}
}

boolean ACPI_Enable(){
	ACPI_FADT* fadt = ACPI_FADT_GetInstance();
	if(ACPI_FADT_IsValid()){
		outb(fadt->SMI_CommandPort,fadt->AcpiEnable);
		return True;
	} else {
		return False;
	}
}
