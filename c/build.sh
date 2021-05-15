#!/usr/bin/env bash

set -e
export current_dir=$(cd "$(dirname "$0")";pwd)
cd "${current_dir}"

export src_dir="${current_dir}/src"
export target_dir="${current_dir}/target"

make -C "${src_dir}"
rm -rf "${target_dir}"
mkdir -p "${target_dir}"
mv src/*.o "${target_dir}"
mv src/*.bin "${target_dir}"
mv src/*.elf "${target_dir}"
mv src/*.map "${target_dir}"

objdump -h "${target_dir}/kernel.elf"

mkdir -p "${target_dir}/isofiles/boot/grub"
cp grub.cfg "${target_dir}/isofiles/boot/grub/grub.cfg"
cp "${target_dir}/kernel.bin" "${target_dir}/isofiles/boot/kernel.bin"
grub-mkrescue -o "${target_dir}/LeiOS.iso" "${target_dir}/isofiles"
