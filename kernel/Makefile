BUILDTYPE 		?= Debug
UNAME_S 		?= $(shell uname -s)
CROSS_PREFIX 		?= x86_64-elf

KERNEL_TARGET_DIR 	?= $(CURDIR)/target

ASM			?= nasm
CC			?= gcc
LD			?= ld
OBJCOPY			?= objcopy
OBJDUMP			?= objdump
# use x86_64-elf-gcc on macOS
ifeq "$(UNAME_S)" "Darwin"
	override CC 		:= $(CROSS_PREFIX)-gcc
	override LD 		:= $(CROSS_PREFIX)-ld
	override OBJCOPY 	:= $(CROSS_PREFIX)-objcopy
	override OBJDUMP 	:= $(CROSS_PREFIX)-objdump
endif

ASMBFLAGS 		?= -g -f elf -F dwarf
CFLAGS 			?= -g -c -std=c17 -ggdb -nostdlib -fno-builtin -static -m32 -Wall \
				-Wshadow -W -Wconversion -Wno-sign-conversion  -fno-stack-protector \
				-fomit-frame-pointer -fno-builtin -fno-common  -ffreestanding \
				-Wno-unused-parameter -Wunused-variable -Werror
LDFLAGS 		?= -static -T kernel.lds -n -Map kernel.map
OJCYFLAGS 		?= -O binary

# strip debug symbols
ifeq "$(BUILDTYPE)" "Release"
	override LDFLAGS += -s
	override OJCYFLAGS += -S
	override CFLAGS += -Os -DNDEBUG
else
	override CFLAGS += -O0
endif

KERNEL_OBJS 	:= $(KERNEL_TARGET_DIR)/boot.o \
			$(KERNEL_TARGET_DIR)/libk.o \
			$(KERNEL_TARGET_DIR)/debug.o \
			$(KERNEL_TARGET_DIR)/io.o \
			$(KERNEL_TARGET_DIR)/vgastr.o \
			$(KERNEL_TARGET_DIR)/vga.o \
			$(KERNEL_TARGET_DIR)/cpuid.o \
			$(KERNEL_TARGET_DIR)/cpu/idt.o \
				$(KERNEL_TARGET_DIR)/cpu/isr.o \
				$(KERNEL_TARGET_DIR)/cpu/ports.o \
				$(KERNEL_TARGET_DIR)/cpu/timer.o \
				$(KERNEL_TARGET_DIR)/cpu/interrupt.o \
			$(KERNEL_TARGET_DIR)/main.o

KERNEL_ELF 	?= $(KERNEL_TARGET_DIR)/kernel.elf
KERNEL_BIN 	?= $(KERNEL_TARGET_DIR)/kernel.bin

.PHONY: build clean directories all link bin variables

all: clean directories build link bin

clean:
	rm -f *.o *.bin *.elf *.map
	mkdir -p "$(KERNEL_TARGET_DIR)" && cd "$(KERNEL_TARGET_DIR)" && rm -f *.o *.bin *.elf *.map

directories:
	mkdir -p $(KERNEL_TARGET_DIR)
	mkdir -p $(KERNEL_TARGET_DIR)/cpu

variables:
	@printf "    BUILDTYPE          $(BUILDTYPE)\n"
	@printf "    UNAME_S            $(UNAME_S)\n"
	@printf "    CROSS_PREFIX       $(CROSS_PREFIX)\n"
	@printf "    ASM                $(ASM)\n"
	@printf "    CC                 $(CC)\n"
	@printf "    LD                 $(LD)\n"
	@printf "    OBJCOPY            $(OBJCOPY)\n"
	@printf "    OBJDUMP            $(OBJDUMP)\n"
	@printf "    ASMBFLAGS          $(ASMBFLAGS)\n"
	@printf "    CFLAGS             $(CFLAGS)\n"
	@printf "    LDFLAGS            $(LDFLAGS)\n"
	@printf "    OJCYFLAGS          $(OJCYFLAGS)\n"
	@printf "    KERNEL_OBJS        $(KERNEL_OBJS)\n"
	@printf "    KERNEL_ELF         $(KERNEL_ELF)\n"
	@printf "    KERNEL_BIN         $(KERNEL_BIN)\n"
	@printf "    KERNEL_TARGET_DIR  $(KERNEL_TARGET_DIR)\n"

build: $(KERNEL_OBJS)

link: $(KERNEL_ELF)
$(KERNEL_ELF): $(KERNEL_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(KERNEL_OBJS)
	$(OBJDUMP) -h $(KERNEL_ELF)
bin: $(KERNEL_BIN)
$(KERNEL_BIN): $(KERNEL_ELF)
	$(OBJCOPY) $(OJCYFLAGS) $< $@

$(KERNEL_TARGET_DIR)/%.o : %.asm
	$(ASM) $(ASMBFLAGS) -o $@ $<
$(KERNEL_TARGET_DIR)/%.o : %.c
	$(CC) $(CFLAGS) -o $@ $<
