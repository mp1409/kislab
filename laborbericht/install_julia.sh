#!/usr/bin/env sh

rm julia-0.4.5-linux*.tar.gz*
bit=`uname -m`

if [ "$bit" = "x86_64" ]; then
    wget https://julialang.s3.amazonaws.com/bin/linux/x64/0.4/julia-0.4.5-linux-x86_64.tar.gz
else
    wget https://julialang.s3.amazonaws.com/bin/linux/x86/0.4/julia-0.4.5-linux-i686.tar.gz
fi

tar -xzf julia-0.4.5-linux*.tar.gz* -C julia/
rm julia-0.4.5-linux*.tar.gz*

./install_julia_pkgs.sh
