#!/usr/bin/env bash

qemu-system-x86_64 -drive format=raw,file=target/LeiOS.bin -nographic -m 16 -ctrl-grab -no-reboot
# Ctrl-A X 退出
# Ctrl-A H 帮助
