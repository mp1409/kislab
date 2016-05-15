#!/usr/bin/env sh

cd $(dirname $(readlink -f "$0"))
./build_platform uno
