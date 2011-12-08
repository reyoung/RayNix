#include "../cpuid.h"
#include "stdint.h"

enum CPUID_Query_Type{
	CQT_VendorString=0,
	CQT_Feature,
};


static inline void cpuid(int code, uint32_t *a, uint32_t* b, uint32_t* c,uint32_t *d) {
  __asm__ volatile("cpuid":
		  "=a"(*a),"=d"(*d),"=b"(*b),"=c"(*c):"0"(code));
}


static inline int cpuid_string(int code, uint32_t where[4]) {
  int highest;
  __asm__ volatile("cpuid":"=a"(*where),"=b"(*(where+1)),
               "=c"(*(where+2)),"=d"(*(where+3)):"0"(code));
  return highest;
}



void CPUID_GetVendorString(char* outstr){
	uint32_t Reg[4];
	cpuid_string(CQT_VendorString,Reg);
	uint32_t * p = outstr;
	p[0] = Reg[1];
	p[1] = Reg[3];
	p[2] = Reg[2];
	outstr[12]=0;
}

uint64_t CPUID_GetFeature(){
	uint32_t a,b,c,d;
	cpuid(CQT_Feature,&a,&b,&c,&d);
	uint64_t retv = (c<<32);
	retv|=d;
	return retv;
}
