#!/usr/bin/env sh
cppcheck -q -v --std=c++11 \
	--enable=warning,style,performance,portability,unusedFunction \
	src
