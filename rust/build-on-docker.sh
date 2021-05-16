#!/usr/bin/env bash

set -e
export current_dir=$(cd "$(dirname "$0")";pwd)
cd "${current_dir}"

export cargo_cache_dir="${current_dir}/tmp/cargo/registry/cache"
export cargo_index_dir="${current_dir}/tmp/cargo/registry/index"
export target_dir="${current_dir}/tmp/target"
mkdir -p "${cargo_cache_dir}"
mkdir -p "${target_dir}"

export docker_run="docker run -it --rm -v "$(pwd):$(pwd)" -w "$(pwd)" --name "Build-LeiOS-$(date +%Y%m%d-%H%M%S)" -v "${cargo_cache_dir}:/usr/local/cargo/registry/cache" -v "${cargo_index_dir}:/usr/local/cargo/registry/index" -v "${target_dir}:$(pwd)/target" leios-build-rust"

if [ -n "$1" ]
then
    $docker_run $1
else
    $docker_run ./build2.sh
fi

cp "${target_dir}/LeiOS.iso" "${current_dir}/LeiOS.iso"
