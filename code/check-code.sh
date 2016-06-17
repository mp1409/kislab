#!/usr/bin/env sh
find kislab | grep -E '*.(cpp|ino)$' | xargs cppcheck -q -v --std=c++11 \
	--error-exitcode=1 --enable=warning,style,performance,portability
