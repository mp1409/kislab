#!/usr/bin/env sh

which rsvg-convert
retval=$?

if [ $retval -eq 0 ]; then
    for i in UML/*.svg 
    do
        name=`basename $i .svg`
        rsvg-convert -f pdf -o UML/${name}.pdf $i
    done
fi

pdflatex Laborbericht.tex
pdflatex Laborbericht.tex
pdflatex Laborbericht.tex
pdflatex Laborbericht.tex
