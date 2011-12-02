CC=i586-elf-gcc
CFLAGS=-Wall -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -c
LD=i586-elf-ld
LFLAGS=-T linker.ld
ASM=nasm
RLIBC=rlibc.a
AR=i586-elf-ar
all:
	$(MAKE) -C rlibc static_lib
	@cp rlibc/$(RLIBC) lib/$(RLIBC)
	$(MAKE) -C kernel kernel
	@cp kernel/kernel.a lib/kernel.a
	$(LD) $(LFLAGS) -o kernel.bin  lib/kernel.a lib/$(RLIBC)
run:all
	qemu.exe -kernel kernel.bin
clean:
	rm lib/*
	$(MAKE) -C rlibc clean
	$(MAKE) -C kernel clean
	rm kernel.bin