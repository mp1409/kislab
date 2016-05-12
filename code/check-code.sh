#!/usr/bin/env sh
find kislab | grep -E '*.(h|cc|ino)' | xargs cppcheck -q -v --std=c++11 \
	--enable=warning,style,performance,portability
