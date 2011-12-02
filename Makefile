CC=i586-elf-gcc
CFLAGS=-Wall -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -c
LD=i586-elf-ld
LFLAGS=-T linker.ld
ASM=nasm
RLIBC=rlibc.a
all:
	$(MAKE) -C rlibc static_lib
	@cp rlibc/$(RLIBC) lib/$(RLIBC)
clean:
	rm lib/$(RLIBC)
	$(MAKE) -C rlibc clean