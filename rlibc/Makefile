CC=i586-elf-gcc
CFLAGS=-Wall -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -c
LD=i586-elf-ld
AR=i586-elf-ar
LFLAGS=-T linker.ld
ASM=nasm
INC = inc
RLIBC=rlibc.a

RLIBC_SRC_CC_FILES=$(wildcard src/*.c)
RLIBC_OBJS_FILES=$(patsubst %.c, %.o, $(RLIBC_SRC_CC_FILES))

static_lib:$(RLIBC_OBJS_FILES)
	$(AR) -r $(RLIBC) $(RLIBC_OBJS_FILES)
clean:
	rm $(RLIBC)
	rm $(RLIBC_OBJS_FILES)
%.o: %.c
	@echo "Compiling $(DIR)/$< Using $(CC)"
	$(CC) $(CFLAGS) -I$(INC) -o $@ -c $<
	