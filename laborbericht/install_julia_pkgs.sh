#!/usr/bin/env sh

string="Pkg.update(); Pkg.add(\"Gadfly\"); Pkg.add(\"Cairo\"); Pkg.add(\"CurveFit\");"


# Test if julia is in path
julia --version
retval=$?

if [ $retval -eq 127 ]; then
	echo $string | ./julia/julia-2ac304dfba/bin/julia
else
	echo $string | julia
fi
