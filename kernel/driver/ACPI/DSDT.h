#ifndef KERNEL_DRIVER_ACPI_DSDT_H
#define KERNEL_DRIVER_ACPI_DSDT_H
#include "stdint.h"

#define ACPI_DSDT_SLP_EN 1<<13

typedef struct tagACPI_DSDT_Header{
	char Signature[4];
	uint32_t Length;
	uint8_t Revision;
	uint8_t Checksum;
	char  OEMID[6];
	char  OEMTableID[8];
	uint32_t OEMRevision;
	uint32_t CreatorID;
	uint32_t CreatorRevision;
}ACPI_DSDT_Header;

void*  ACPI_DSDT_GetS5Object();

uint16_t ACPI_DSDT_S5_Get_SLP_TYPa();

uint16_t ACPI_DSDT_S5_Get_SLP_TYPb();

ACPI_DSDT_Header* ACPI_DSDT_GetHeader();

boolean ACPI_DSDT_IsValid();

void ACPI_DSDT_Dump();


#endif
