#!/usr/bin/env bash

cd $(dirname $(readlink -f "$0"))
source <(curl -SLs https://raw.githubusercontent.com/adafruit/travis-ci-arduino/master/install.sh)
