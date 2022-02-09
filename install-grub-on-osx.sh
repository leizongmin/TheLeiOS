#!/usr/bin/env bash

# ref: https://wiki.osdev.org/GRUB#Installing_GRUB_2_on_OS_X

echo "Installing objconv"
cd tools/objconv
./build.sh
cp objconv /usr/local/bin/objconv
cd ../..

echo "Installing dependencies"
brew install xorriso mtools

echo "Installing grub"
echo ""
git clone git://git.savannah.gnu.org/grub.git
cd grub
./bootstrap && ./configure --disable-werror TARGET_CC=x86_64-elf-gcc TARGET_OBJCOPY=x86_64-elf-objcopy \
                 TARGET_STRIP=x86_64-elf-strip TARGET_NM=x86_64-elf-nm TARGET_RANLIB=x86_64-elf-ranlib --target=x86_64-elf
make
make install
cd ..
cp tools/fonts/unicode.pf2 /usr/local/share/grub/unicode.pf2
