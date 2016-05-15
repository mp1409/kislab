#!/usr/bin/env sh

# Test if julia is in path
julia --version
retval=$?

if [ $retval -eq 127 ]; then
	./julia/julia-2ac304dfba/bin/julia julia/*.j
else
	julia julia/*.j
fi

./build_withoutplots.sh
