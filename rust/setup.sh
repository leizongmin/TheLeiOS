#!/usr/bin/env bash

set -e
export current_dir=$(cd "$(dirname "$0")";pwd)
cd "${current_dir}"

rustup default nightly
rustup target add thumbv7em-none-eabihf
rustup component add llvm-tools-preview
rustup component add rust-src
cargo install bootimage
