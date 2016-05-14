#!/usr/bin/env sh

echo "Pkg.update()\nPkg.add(\"Gadfly\")\nPkg.add(\"Cairo\")" | ./julia/julia-2ac304dfba/bin/julia
./julia/julia-2ac304dfba/bin/julia julia/*.j

./build_withoutplots.sh
