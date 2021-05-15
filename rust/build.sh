#!/usr/bin/env bash

set -e
export current_dir=$(cd "$(dirname "$0")";pwd)
cd "${current_dir}"

export target_dir="${current_dir}/target"

cargo build --release
cargo bootimage --release
