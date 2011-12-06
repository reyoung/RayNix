CC=i586-elf-gcc -std=c99
CFLAGS=-Wall -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -c
LD=i586-elf-ld
LFLAGS=-T linker.ld
AS=nasm
AS_FLAG= -f elf
BASIC_DIRVER_CC_FILE=$(wildcard driver/*.c) $(wildcard driver/ACPI/*.c) $(wildcard driver/mm/*.c)
BASIC_ASM_FILE=$(wildcard driver/*.S)
OBJS=kernel.o loader.o $(patsubst %.c, %.o, $(BASIC_DIRVER_CC_FILE)) $(patsubst %.S, %.o, $(BASIC_ASM_FILE))
AR=i586-elf-ar
INCLUDE_OPTIONS=-I../rlibc/inc 





kernel:	$(OBJS)
	@echo $(OBJS)
	$(AR) -r  kernel.a $(OBJS)
run:kernel
	qemu.exe -kernel kernel.bin
clean:
	rm *.o *.a
	rm driver/*.o
%.o:%.c
	$(CC) $(CFLAGS) -o  $@ $(INCLUDE_OPTIONS) $<
%.o:%.S
	$(AS) $(AS_FLAG) -o $@ $<
loader.o:loader.S
	$(AS) $(AS_FLAG) loader.s
