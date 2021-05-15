#!/usr/bin/env bash

set -e
export current_dir=$(cd "$(dirname "$0")";pwd)
cd "${current_dir}"

qemu-system-x86_64 -drive format=raw,file=target/leios/release/bootimage-leios.bin -m 16 -no-reboot
