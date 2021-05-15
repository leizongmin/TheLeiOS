#!/usr/bin/env bash

make -C src
mkdir -p target
mv src/*.o target
mv src/*.bin target
mv src/*.elf target
mv src/*.map target
