#include "RSDT.h"
#include "RSDP.h"

ACPI_RSDT_Header* ACPI_RSDT_GetHeader(){
	if(RSDP_IsValid()){
		RSDP_Descriptor_V10* desc = RSDP_GetDescriptor();
		return (ACPI_RSDT_Header*)(desc->RsdtAddress);	
	} else {
		return 0;
	}
}

boolean ACPI_RSDT_IsValid(){
	ACPI_RSDT_Header* header = ACPI_RSDT_GetHeader();
	if(header!=0){
		char* p = (char * )header;
		uint8_t cksum = 0;
		for(int i=0;i<header->Length;++i){
			cksum += p[i];
		}
		return cksum == 0;
	} else {
		return 0;
	}
}


void* ACPI_RSDT_GetEntry(const char* sig){
	if(ACPI_RSDT_IsValid()){
		ACPI_RSDT_Header* h = ACPI_RSDT_GetHeader();
		int entries = (h->Length - sizeof(ACPI_RSDT_Header)) / 4;
		void** entriesPointers = &h[1];
		for(int i=0;i<entries;++i){
			ACPI_RSDT_Header* temp = (ACPI_RSDT_Header*) entriesPointers[i];
			if(strncmp(temp->Signature,sig,4)==0){
				return temp;
			}
		}
		return 0;
	} else {
		return 0;
	}
}
