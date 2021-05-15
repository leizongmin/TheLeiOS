#!/usr/bin/env bash

qemu-system-x86_64 -drive format=raw,file=target/LeiOS.bin -nographic
