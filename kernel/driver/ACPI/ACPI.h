#ifndef KERNEL_DRIVER_ACPI_H_INCLUDED
#define KERNEL_DRIVER_ACPI_H_INCLUDED

#include "stddef.h"

boolean ACPI_IsEnabled();

boolean ACPI_Enable();

void ACPI_Shutdown();

#endif
