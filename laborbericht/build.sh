#!/usr/bin/env sh

# Test if julia is in path
julia --version
retval=$?

if [ $retval -eq 127 ]; then
	./julia/julia-2ac304dfba/bin/julia julia/*.j
	./julia/julia-2ac304dfba/bin/julia julia/csv.jx julia/*.csv
else
	julia julia/*.j
	julia julia/csv.jx julia/*.csv
fi

./build_withoutplots.sh
