#!/usr/bin/env bash

set -e
export current_dir=$(cd "$(dirname "$0")";pwd)
cd "${current_dir}"

if [ -n "$1" ]
then
    docker run -it --rm -v "$(pwd):$(pwd)" -w "$(pwd)" --name "Build-LeiOS-$(date +%Y%m%d-%H%M%S)" rust:1.52 $1
else
    docker run -it --rm -v "$(pwd):$(pwd)" -w "$(pwd)" --name "Build-LeiOS-$(date +%Y%m%d-%H%M%S)" rust:1.52 ./build.sh
fi
