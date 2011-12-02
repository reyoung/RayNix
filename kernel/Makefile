CC=i586-elf-gcc
CFLAGS=-Wall -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -c
LD=i586-elf-ld
LFLAGS=-T linker.ld
AS=nasm
AS_FLAG= -f elf
OBJS=kernel.o loader.o
AR=i586-elf-ar
INCLUDE_OPTIONS=-I../rlibc/inc 

kernel:	$(OBJS)
	$(AR) -r  kernel.a $(OBJS)
run:kernel
	qemu.exe -kernel kernel.bin
clean:
	rm *.o *.a
kernel.o:kernel.c
	$(CC) $(CFLAGS) $(INCLUDE_OPTIONS) kernel.c
loader.o:loader.S
	$(AS) $(AS_FLAG) loader.s