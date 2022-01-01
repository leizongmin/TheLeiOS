ASM		?= nasm
CC		?= gcc
LD		?= ld
OBJCOPY		?= objcopy

ASMBFLAGS 	?= -g -f elf -F dwarf
CFLAGS 		?= -g -c -std=c17 -ggdb -nostdlib -m32 -Wall -Wshadow -W -Wconversion -Wno-sign-conversion  -fno-stack-protector -fomit-frame-pointer -fno-builtin -fno-common  -ffreestanding  -Wno-unused-parameter -Wunused-variable -Werror
LDFLAGS 	?= -static -T kernel.lds -n -Map kernel.map
OJCYFLAGS 	?= -O binary

# strip debug symbols
BUILDTYPE 	?= Debug
ifeq "$(BUILDTYPE)" "Release"
	override LDFLAGS += -s
	override OJCYFLAGS += -S
	override CFLAGS += -Oz
else
	override CFLAGS += -O1
endif

KERNEL_OBJS 	:= boot.o main.o vgastr.o
KERNEL_ELF 	?= kernel.elf
KERNEL_BIN 	?= kernel.bin

.PHONY: build clean all link bin variables

all: clean build link bin

clean:
	$(RM) -f *.o *.bin *.elf *.map

variables:
	@printf "    BUILDTYPE        $(BUILDTYPE)\n"
	@printf "    ASM              $(ASM)\n"
	@printf "    CC               $(CC)\n"
	@printf "    LD               $(LD)\n"
	@printf "    OBJCOPY          $(OBJCOPY)\n"
	@printf "    ASMBFLAGS        $(ASMBFLAGS)\n"
	@printf "    CFLAGS           $(CFLAGS)\n"
	@printf "    LDFLAGS          $(LDFLAGS)\n"
	@printf "    OJCYFLAGS        $(OJCYFLAGS)\n"
	@printf "    KERNEL_OBJS      $(KERNEL_OBJS)\n"
	@printf "    KERNEL_ELF       $(KERNEL_ELF)\n"
	@printf "    KERNEL_BIN       $(KERNEL_BIN)\n"

build: $(KERNEL_OBJS)

link: $(KERNEL_ELF)
$(KERNEL_ELF): $(KERNEL_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(KERNEL_OBJS)
bin: $(KERNEL_BIN)
$(KERNEL_BIN): $(KERNEL_ELF)
	$(OBJCOPY) $(OJCYFLAGS) $< $@

%.o : %.asm
	$(ASM) $(ASMBFLAGS) -o $@ $<
%.o : %.c
	$(CC) $(CFLAGS) -o $@ $<
