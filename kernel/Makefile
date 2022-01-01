MAKEFLAGS 		?= -sR
MKDIR 			?= mkdir
RMDIR 			?= rmdir
CP 				?= cp
CD 				?= cd
DD 				?= dd
RM 				?= rm

ASM				?= nasm
CC				?= gcc
LD				?= ld
OBJCOPY			?= objcopy

ASMBFLAGS 		?= -f elf -w-orphan-labels
CFLAGS 			?= -c -Os -std=c17 -m32 -Wall -Wshadow -W -Wconversion -Wno-sign-conversion  -fno-stack-protector -fomit-frame-pointer -fno-builtin -fno-common  -ffreestanding  -Wno-unused-parameter -Wunused-variable
LDFLAGS 		?= -s -static -T kernel.lds -n -Map kernel.map
OJCYFLAGS 		?= -S -O binary

KERNEL_OBJS 	:= boot.o main.o vgastr.o
KERNEL_ELF 		?= kernel.elf
KERNEL_BIN 		?= kernel.bin

.PHONY: build clean all link bin variables

all: clean build link bin

clean:
	$(RM) -f *.o *.bin *.elf

variables:
	@printf "    ASM              $(ASM)\n"
	@printf "    CC               $(CC)\n"
	@printf "    LD               $(LD)\n"
	@printf "    OBJCOPY          $(OBJCOPY)\n"
	@printf "    MAKEFLAGS        $(MAKEFLAGS)\n"
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