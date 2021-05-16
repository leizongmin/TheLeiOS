#!/usr/bin/env bash

set -e
export current_dir=$(cd "$(dirname "$0")";pwd)
cd "${current_dir}"

export docker_run="docker run -it --rm -v "$(pwd):$(pwd)" -w "$(pwd)" --name "Build-LeiOS-$(date +%Y%m%d-%H%M%S)" leios-build"

if [ -n "$1" ]
then
    $docker_run $1
else
    $docker_run ./build.sh
fi
