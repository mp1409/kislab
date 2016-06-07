#!/usr/bin/env sh

# Test if julia is in path
julia --version
retval=$?

if [ $retval -eq 127 ]; then
	./julia/julia-2ac304dfba/bin/julia julia/plot-schematisch.jl
	for i in julia/data/*.csv; do
		./julia/julia-2ac304dfba/bin/julia julia/plot-data.jl $i;
	done

	# ./julia/julia-2ac304dfba/bin/julia julia/plot-csv.jlx julia/*.csv
else
	julia julia/plot-schematisch.jl
	for i in julia/data/*.csv; do
		julia julia/plot-data.jl $i;
	done
	# julia julia/plot-csv.jlx julia/*.csv
fi

./build_withoutplots.sh
