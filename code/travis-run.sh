#!/usr/bin/env bash

cd $(dirname $(readlink -f "$0"))
./build_platform uno
