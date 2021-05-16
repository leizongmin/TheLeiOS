#!/usr/bin/env bash

set -e
export current_dir=$(cd "$(dirname "$0")";pwd)
cd "${current_dir}"

qemu-system-x86_64 -cdrom target/LeiOS.iso -m 16 -no-reboot
