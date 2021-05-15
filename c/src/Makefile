MAKEFLAGS = -sR
MKDIR = mkdir
RMDIR = rmdir
CP = cp
CD = cd
DD = dd
RM = rm

ASM		= nasm
CC		= gcc
LD		= ld
OBJCOPY	= objcopy

ASMBFLAGS	= -f elf -w-orphan-labels
CFLAGS		= -c -Os -std=c99 -m32 -Wall -Wshadow -W -Wconversion -Wno-sign-conversion  -fno-stack-protector -fomit-frame-pointer -fno-builtin -fno-common  -ffreestanding  -Wno-unused-parameter -Wunused-variable
LDFLAGS		= -s -static -T leios.lds -n -Map LeiOS.map
OJCYFLAGS	= -S -O binary

LEIOS_OBJS :=
LEIOS_OBJS += boot.o main.o vgastr.o
LEIOS_ELF = LeiOS.elf
LEIOS_BIN = LeiOS.bin

.PHONY : build clean all link bin

all: clean build link bin

clean:
	$(RM) -f *.o *.bin *.elf

build: $(LEIOS_OBJS)

link: $(LEIOS_ELF)
$(LEIOS_ELF): $(LEIOS_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(LEIOS_OBJS)
bin: $(LEIOS_BIN)
$(LEIOS_BIN): $(LEIOS_ELF)
	$(OBJCOPY) $(OJCYFLAGS) $< $@

%.o : %.asm
	$(ASM) $(ASMBFLAGS) -o $@ $<
%.o : %.c
	$(CC) $(CFLAGS) -o $@ $<
