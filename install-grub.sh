#!/usr/bin/env bash

echo "Installing objconv"
cd tools/objconv
./build.sh
cp objconv /usr/local/bin/objconv
cd ../..

echo "Installing grub"
echo ""
git clone --depth 1 git://git.savannah.gnu.org/grub.git
cd grub
./bootstrap
./configure
make
make install
