UNAME_S 				?= $(shell uname -s)
KERNEL_DIR 				?= $(CURDIR)/kernel
TARGET_DIR 				?= $(CURDIR)/target
DOCKER_IMAGE 			?= leios-build
ISO_FILE 				?= $(TARGET_DIR)/LeiOS.iso

GDB 					?= gdb
DOCKER 					?= docker
QEMU 					?= qemu-system-x86_64
override QEMU_FLAGS 	+= -m 16 -no-reboot -s

BUILD_TARGET_DARWIN 	:= docker
BUILD_TARGET_DEFAULT 	:= iso

.PHONY: all init clean help kernel iso docker-image docker run

all:
	@if [ "$(UNAME_S)" = "Darwin" ]; then\
		$(MAKE) $(BUILD_TARGET_DARWIN);\
	else\
		$(MAKE) $(BUILD_TARGET_DEFAULT);\
	fi

$(ISO_FILE):
	@if [ "$(UNAME_S)" = "Darwin" ]; then\
		$(MAKE) $(BUILD_TARGET_DARWIN);\
	else\
		$(MAKE) $(BUILD_TARGET_DEFAULT);\
	fi

clean:
	make -C "$(KERNEL_DIR)" clean
	rm -rf "$(TARGET_DIR)"

init:
	@if [ "$(UNAME_S)" = "Darwin" ]; then\
		$(MAKE) docker-image;\
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
	@printf "    docker           Build on docker container (doe none Linux system)\n"
	@printf "    run              Run on the QEMU virtual machine\n"
	@printf "    gdb              Start GDB remote debugging\n"
	@printf "\n"
	@printf "\n"
	@printf "Variables:\n"
	@printf "\n"
	@printf "    CC               $(CC)\n"
	@printf "    UNAME_S          $(UNAME_S)\n"
	@printf "    KERNEL_DIR       $(KERNEL_DIR)\n"
	@printf "    TARGET_DIR       $(TARGET_DIR)\n"
	@printf "    DOCKER_IMAGE     $(DOCKER_IMAGE)\n"
	@printf "    ISO_FILE         $(ISO_FILE)\n"
	@printf "    DOCKER           $(DOCKER)\n"
	@printf "    QEMU             $(QEMU)\n"
	@printf "    QEMU_FLAGS       $(QEMU_FLAGS)\n"
	@printf "\n"
	@printf "Variables for make kernel:\n"
	@printf "\n"
	@$(MAKE) -C "$(KERNEL_DIR)" variables
	@printf "\n"

kernel:
	make -C "$(KERNEL_DIR)"

iso: kernel
	mkdir -p "$(TARGET_DIR)"
	rm -rf "$(TARGET_DIR)"
	objdump -h "$(KERNEL_DIR)/kernel.elf"
	mkdir -p "$(TARGET_DIR)/isofiles/boot/grub"
	cp grub.cfg "$(TARGET_DIR)/isofiles/boot/grub/grub.cfg"
	cp "$(KERNEL_DIR)/kernel.bin" "$(TARGET_DIR)/isofiles/boot/kernel.bin"
	grub-mkrescue -o "$(ISO_FILE)" "$(TARGET_DIR)/isofiles"

docker-image:
	$(DOCKER) build -t $(DOCKER_IMAGE) -f builder_Dockerfile $(CURDIR)

docker:
	$(DOCKER) run -it --rm --name "Build-LeiOS-$(date +%Y%m%d-%H%M%S)"\
		-v "$(CURDIR):$(CURDIR)" -w "$(CURDIR)"\
		$(DOCKER_IMAGE) bash -c "make"

run: $(ISO_FILE)
	$(QEMU) -cdrom "$(ISO_FILE)" $(QEMU_FLAGS)

gdb:
	$(GDB) -ex "target remote localhost:1234"
