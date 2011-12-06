#ifndef KERNEL_DRIVER_CMOS_H
#define KERNEL_DRIVER_CMOS_H
#include "stdint.h"

#define CMOS_DATE_ISBINARY 0x04

#define CMOS_STATE_B_OFFSET 0x0B

#define CMOS_SECOND_OFFSET 0x00
#define CMOS_MIN_OFFSET	   0x02
#define CMOS_HOUR_OFFSET   0x04
#define CMOS_DAY_OF_MONTH_OFFSET 0x07
#define CMOS_MONTH_OFFSET 0x08
#define CMOS_YEAR_OFFSET 0x09

typedef struct tagCMOS_DateTime{
	uint8_t Hour;
	uint8_t Min;
	uint8_t Second;
	
	uint8_t Day;
	uint8_t Month;
	uint8_t Year;
}CMOS_DateTime __attribute__((packed));

void CMOS_ReadAll(uint8_t* buffer);
void CMOS_Write(uint8_t* buffer);

void CMOS_GetCurrentDateTime(CMOS_DateTime* dt);

#endif
