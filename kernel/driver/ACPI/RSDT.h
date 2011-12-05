#ifndef KERNEL_DRIVER_ACPI_RSDT_H_INCLUDED
#define KERNEL_DRIVER_ACPI_RSDT_H_INCLUDED
#include "stdint.h"
typedef struct tagACPI_RSDT_HEADER{
	char Signature[4];
	uint32_t Length;
	uint8_t Revision;
	uint8_t Checksum;
	char  OEMID[6];
	char  OEMTableID[8];
	uint32_t OEMRevision;
	uint32_t CreatorID;
	uint32_t CreatorRevision;
}ACPI_RSDT_Header;

ACPI_RSDT_Header* ACPI_RSDT_GetHeader();


#endif
