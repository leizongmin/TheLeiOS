BUILDTYPE 		?= Debug
UNAME_S 		?= $(shell uname -s)
CROSS_PREFIX 		?= x86_64-elf

KERNEL_TARGET_DIR 	?= $(CURDIR)/target

ASM			?= nasm
CC			?= gcc
CXX 			?= g++
LD			?= ld
OBJCOPY			?= objcopy
OBJDUMP			?= objdump
# use x86_64-elf-gcc on macOS
ifeq "$(UNAME_S)" "Darwin"
	override CC 		:= $(CROSS_PREFIX)-gcc
	override CXX 		:= $(CROSS_PREFIX)-g++
	override LD 		:= $(CROSS_PREFIX)-ld
	override OBJCOPY 	:= $(CROSS_PREFIX)-objcopy
	override OBJDUMP 	:= $(CROSS_PREFIX)-objdump
endif

ASFLAGS 		?= -g -f elf -F dwarf
CFLAGS 			?= -g -c -std=c17 -ggdb -nostdlib -fno-builtin -static -m32 -Wall \
				-Wshadow -W -Wconversion -Wno-sign-conversion  -fno-stack-protector \
				-fomit-frame-pointer -fno-builtin -fno-common  -ffreestanding \
				-Wno-unused-parameter -Wunused-variable -Werror \
				-I$(CURDIR)/..
CXXFLAGS 		?= -g -c -std=c++17 -ggdb -nostdlib -fno-builtin -static -m32 -Wall \
				-Wshadow -W -Wconversion -Wno-sign-conversion  -fno-stack-protector \
				-fomit-frame-pointer -fno-builtin -fno-common  -ffreestanding \
				-Wno-unused-parameter -Wunused-variable -Werror \
				-I$(CURDIR)/..
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
			$(KERNEL_TARGET_DIR)/libk/libk.o \
				$(KERNEL_TARGET_DIR)/libk/debug.o \
			$(KERNEL_TARGET_DIR)/arch/i386/io.o \
				$(KERNEL_TARGET_DIR)/arch/i386/cpuid.o \
				$(KERNEL_TARGET_DIR)/arch/i386/idt.o \
				$(KERNEL_TARGET_DIR)/arch/i386/isr.o \
				$(KERNEL_TARGET_DIR)/arch/i386/port.o \
				$(KERNEL_TARGET_DIR)/arch/i386/timer.o \
				$(KERNEL_TARGET_DIR)/arch/i386/interrupt.o \
			$(KERNEL_TARGET_DIR)/drivers/keyboard.o \
				$(KERNEL_TARGET_DIR)/drivers/vgatext.o \
				$(KERNEL_TARGET_DIR)/drivers/vgagraph.o \
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
	mkdir -p $(KERNEL_TARGET_DIR)/arch/i386
	mkdir -p $(KERNEL_TARGET_DIR)/libk
	mkdir -p $(KERNEL_TARGET_DIR)/drivers

variables:
	@printf "    BUILDTYPE          $(BUILDTYPE)\n"
	@printf "    UNAME_S            $(UNAME_S)\n"
	@printf "    CROSS_PREFIX       $(CROSS_PREFIX)\n"
	@printf "    ASM                $(ASM)\n"
	@printf "    CC                 $(CC)\n"
	@printf "    LD                 $(LD)\n"
	@printf "    OBJCOPY            $(OBJCOPY)\n"
	@printf "    OBJDUMP            $(OBJDUMP)\n"
	@printf "    ASFLAGS            $(ASFLAGS)\n"
	@printf "    CFLAGS             $(CFLAGS)\n"
	@printf "    CXXFLAGS           $(CXXFLAGS)\n"
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
	$(ASM) $(ASFLAGS) -o $@ $<
$(KERNEL_TARGET_DIR)/%.o : %.c
	$(CC) $(CFLAGS) -o $@ $<
$(KERNEL_TARGET_DIR)/%.o : %.cc
	$(CXX) $(CXXFLAGS) -o $@ $<
