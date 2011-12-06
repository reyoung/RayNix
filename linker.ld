ENTRY (loader)

SECTIONS
{
    . = 0x00100000;

    .text ALIGN (0x1) :
    {
        *(.text)
    }

    .rodata ALIGN (0x1) :
    {
        *(.rodata*)
    }

    .data ALIGN (0x1) :
    {
        *(.data)
    }

    .bss :
    {
        sbss = .;
        *(COMMON)
        *(.bss)
        ebss = .;
    }
}