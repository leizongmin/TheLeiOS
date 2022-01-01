# docs: https://seisman.github.io/how-to-write-makefile/overview.html

BUILDTYPE 		?= Debug
UNAME_S 		?= $(shell uname -s)
KERNEL_DIR 		?= $(CURDIR)/kernel
TARGET_DIR 		?= $(CURDIR)/target
DOCKER_IMAGE 		?= leios-build
ISO_FILE 		?= $(TARGET_DIR)/LeiOS.iso
KERNEL_BIN_FILE 	?= $(TARGET_DIR)/isofiles/boot/kernel.bin
KERNEL_ELF_FILE 	?= $(TARGET_DIR)/kernel.elf
CONTAINER_NAME 		?= Build-LeiOS-$(shell date +%Y%m%d-%H%M%S)

GDB 			?= gdb
DOCKER 			?= docker
QEMU 			?= qemu-system-x86_64
override QEMU_FLAGS 	+= -smp 2 -m 16M -vga std -no-reboot -D $(TARGET_DIR)/qemu.log -serial file:$(TARGET_DIR)/serial.log -no-shutdown -d int,cpu_reset

BUILD_TARGET_DARWIN 	:= docker
BUILD_TARGET_DEFAULT 	:= iso

# debug mode
ifeq "$(DEBUG)" "1"
	# freeze CPU at startup (use 'c' to start execution)
	override QEMU_FLAGS += -s -S
endif

.PHONY: all init clean help kernel iso docker-image docker run run2 run3 run4

all:
	@if [ "$(UNAME_S)" = "Darwin" ]; then\
		$(MAKE) $(BUILD_TARGET_DARWIN) BUILDTYPE=$(BUILDTYPE);\
	else\
		$(MAKE) $(BUILD_TARGET_DEFAULT) BUILDTYPE=$(BUILDTYPE);\
	fi

$(ISO_FILE):
	@if [ "$(UNAME_S)" = "Darwin" ]; then\
		$(MAKE) $(BUILD_TARGET_DARWIN) BUILDTYPE=$(BUILDTYPE);\
	else\
		$(MAKE) $(BUILD_TARGET_DEFAULT) BUILDTYPE=$(BUILDTYPE);\
	fi

clean:
	$(MAKE) -C "$(KERNEL_DIR)" clean BUILDTYPE=$(BUILDTYPE)
	rm -rf "$(TARGET_DIR)"

init:
	@if [ "$(UNAME_S)" = "Darwin" ]; then\
		$(MAKE) docker-image BUILDTYPE=$(BUILDTYPE);\
	fi

help:
	@printf "The LeiOS\n"
	@printf "=========\n"
	@printf "\n"
	@printf "Usage:\n"
	@printf "\n"
	@printf "    init             Initiate the current build environment \n"
	@printf "    kernel           Build the OS kernel\n"
	@printf "    iso              Build the bootable iso file\n"
	@printf "    docker-image     Make docker image of builder (for none Linux system)\n"
	@printf "    docker           Build on docker container (for none Linux system)\n"
	@printf "    docker-bash      Enter the docker container to manual build (for none Linux system)\n"
	@printf "    run              Run on the QEMU simulator\n"
	@printf "    gdb              Start GDB remote debugging\n"
	@printf "\n"
	@printf "\n"
	@printf "Variables:\n"
	@printf "\n"
	@printf "    BUILDTYPE        $(BUILDTYPE)\n"
	@printf "    CC               $(CC)\n"
	@printf "    UNAME_S          $(UNAME_S)\n"
	@printf "    KERNEL_DIR       $(KERNEL_DIR)\n"
	@printf "    TARGET_DIR       $(TARGET_DIR)\n"
	@printf "    DOCKER_IMAGE     $(DOCKER_IMAGE)\n"
	@printf "    ISO_FILE         $(ISO_FILE)\n"
	@printf "    KERNEL_BIN_FILE  $(KERNEL_BIN_FILE)\n"
	@printf "    KERNEL_ELF_FILE  $(KERNEL_ELF_FILE)\n"
	@printf "    DOCKER           $(DOCKER)\n"
	@printf "    QEMU             $(QEMU)\n"
	@printf "    QEMU_FLAGS       $(QEMU_FLAGS)\n"
	@printf "    DEBUG            $(DEBUG)\n"
	@printf "    CONTAINER_NAME   $(CONTAINER_NAME)\n"
	@printf "\n"
	@printf "Variables for make kernel:\n"
	@printf "\n"
	@$(MAKE) -C "$(KERNEL_DIR)" variables BUILDTYPE=$(BUILDTYPE)
	@printf "\n"

kernel:
	$(MAKE) -C "$(KERNEL_DIR)" BUILDTYPE=$(BUILDTYPE)

iso: kernel
	rm -rf "$(TARGET_DIR)"
	mkdir -p "$(TARGET_DIR)/isofiles/boot/grub"
	cp grub.cfg "$(TARGET_DIR)/isofiles/boot/grub/grub.cfg"
	cp "$(KERNEL_DIR)/kernel.bin" "$(TARGET_DIR)/isofiles/boot/kernel.bin"
	cp "$(KERNEL_DIR)/kernel.elf" "$(TARGET_DIR)/kernel.elf"
	grub-mkrescue -o "$(ISO_FILE)" "$(TARGET_DIR)/isofiles"

docker-image:
	$(DOCKER) build -t $(DOCKER_IMAGE) -f builder_Dockerfile $(CURDIR)

docker:
	$(DOCKER) run -it --rm --name "$(CONTAINER_NAME)"\
		-v "$(CURDIR):$(CURDIR)" -w "$(CURDIR)"\
		$(DOCKER_IMAGE) bash -c "make BUILDTYPE=$(BUILDTYPE)"

docker-bash:
	$(DOCKER) run -it --rm --name "$(CONTAINER_NAME)"\
		-v "$(CURDIR):$(CURDIR)" -w "$(CURDIR)"\
		$(DOCKER_IMAGE) bash

#? QEMU graphic
run: $(ISO_FILE)
	$(QEMU) $(QEMU_FLAGS) -monitor stdio -cdrom "$(ISO_FILE)"
run2: $(ISO_FILE)
	$(QEMU) $(QEMU_FLAGS) -monitor stdio -kernel "$(KERNEL_BIN_FILE)"
#? QEMU console
#? Press Alt + 1 switch to VGA
#? Press Alt + 2 switch to compat_monitor0 console, and type 'quit' to quit
#? Press Alt + 3 switch to serial0 console
#? Press Alt + 4 switch to parallel0 console
run3: $(ISO_FILE)
	$(QEMU) $(QEMU_FLAGS) -curses -cdrom "$(ISO_FILE)"
run4: $(ISO_FILE)
	$(QEMU) $(QEMU_FLAGS) -curses -kernel "$(KERNEL_BIN_FILE)"

gdb:
	$(GDB)
