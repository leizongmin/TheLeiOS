#!/usr/bin/env bash

set -e
export current_dir=$(cd "$(dirname "$0")";pwd)
cd "${current_dir}"

docker build -t leios-build-rust .
