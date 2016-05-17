#!/usr/bin/env sh

# Test if julia is in path
julia --version
retval=$?

if [ $retval -eq 127 ]; then
	./julia/julia-2ac304dfba/bin/julia julia/*.jl
	./julia/julia-2ac304dfba/bin/julia julia/plot-csv.jlx julia/*.csv
else
	julia julia/*.jl
	julia julia/plot-csv.jlx julia/*.csv
fi

./build_withoutplots.sh
