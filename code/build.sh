#!/usr/bin/env sh

if [ "$(uname -s)" == "Darwin" ]; then
	/Applications/Arduino.app/Contents/MacOS/Arduino --verify kislab/kislab.ino
else
	arduino --verify kislab/kislab.ino
fi
