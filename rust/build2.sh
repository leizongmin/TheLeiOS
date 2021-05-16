#!/usr/bin/env bash

set -e
export current_dir=$(cd "$(dirname "$0")";pwd)
cd "${current_dir}"

export target_dir="${current_dir}/target"

cargo build --release
objdump -h "${target_dir}/leios_x86_64/release/leios"

mkdir -p "${target_dir}/isofiles/boot/grub"
cp grub.cfg "${target_dir}/isofiles/boot/grub/grub.cfg"
cp "${target_dir}/leios_x86_64/release/leios" "${target_dir}/isofiles/boot/kernel.bin"
grub-mkrescue -o "${target_dir}/LeiOS.iso" "${target_dir}/isofiles"
