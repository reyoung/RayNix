#ifndef KERNEL_DRIVER_RSDP_H_INCLUDED
#define KERNEL_DRIVER_RSDP_H_INCLUDED
#include "stdint.h"
// Reference http://wiki.osdev.org/RSDP
typedef struct tagRSDP_Descriptor_V10 {
	char Signature[8];
	uint8_t Checksum;
	char OEMID[6];
	uint8_t Revision;
	uint32_t RsdtAddress;
}RSDP_Descriptor_V10;

typedef struct tagRSDP_Descriptor_V20 {
	char Signature[8];
	uint8_t Checksum;
	char OEMID[6];
	uint8_t Revision;
	uint32_t RsdtAddress;

	uint32_t Length;
	uint64_t XsdtAddress;
	uint8_t  ExtendedChecksum;
	uint8_t  reserved[3];
}RSDP_Descriptor_V20;

int RSDP_GetVersion();

//! \return RSDP_DESCRIPTOR_V10* or RSDP_DESCRIPTOR_V20*
void* RSDP_GetDescriptor();

//! \return true if valid.
// TODO Test RSDP in APCI 2.0
boolean RSDP_IsValid();



#endif
