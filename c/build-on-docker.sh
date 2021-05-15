#!/usr/bin/env bash

docker run -it --rm -v "$(pwd):$(pwd)" -w "$(pwd)" --name "Build-LeiOS-$(date +%Y%m%d-%H%M%S)" leios-build ./build.sh
