#include "ACPI.h"
#include "FADT.h"
#include "DSDT.h"
#include "../io.h"
#include "../console.h"
#include "../InlineASM.h"
boolean ACPI_IsEnabled(){
	ACPI_FADT* fadt = ACPI_FADT_GetInstance();
	if(ACPI_FADT_IsValid()){
		uint32_t Port = fadt->PM1aControlBlock;
		uint32_t SCI_EN = 1;
		return inb(Port)&SCI_EN;
	} else {
		return False;
	}
}

boolean ACPI_Enable(){
	ACPI_FADT* fadt = ACPI_FADT_GetInstance();
	if(ACPI_FADT_IsValid()){
		outb(fadt->SMI_CommandPort,fadt->AcpiEnable);
		Console_Printf("SMI_PORT %x, ENABLED %x, FADT Is Valid %d \r\n",(int)fadt->SMI_CommandPort,(int)fadt->AcpiEnable,ACPI_FADT_IsValid());
		return True;
	} else {
		return False;
	}
}

void ACPI_Shutdown(){
	ACPI_FADT* fadt = ACPI_FADT_GetInstance();
	uint32_t pm1aCnt = fadt->PM1aControlBlock;
	uint16_t data = ACPI_DSDT_SLP_EN| (uint16_t)ACPI_DSDT_S5_Get_SLP_TYPa();
	uint32_t pm1bCnt = fadt->PM1bControlBlock;
	outw(pm1aCnt,data);
	if(pm1bCnt){
		data = ACPI_DSDT_SLP_EN | ACPI_DSDT_S5_Get_SLP_TYPb();
		outw(pm1bCnt,data);
	}
}
