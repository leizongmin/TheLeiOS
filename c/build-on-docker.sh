#!/usr/bin/env bash

set -e
export current_dir=$(cd "$(dirname "$0")";pwd)
cd "${current_dir}"

# docker run -it --rm -v "$(pwd):$(pwd)" -w "$(pwd)" --name "Build-LeiOS-$(date +%Y%m%d-%H%M%S)" leios-build ./build.sh
docker run -it --rm -v "$(pwd):$(pwd)" -w "$(pwd)" --name "Build-LeiOS-$(date +%Y%m%d-%H%M%S)" leios-build
