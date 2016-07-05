#!/usr/bin/env sh

for i in UML/*.svg
do
	name=`basename $i .svg`
	rsvg-convert -f pdf -o UML/${name}.pdf $i
done

pdflatex Laborbericht.tex
pdflatex Laborbericht.tex
pdflatex Laborbericht.tex
pdflatex Laborbericht.tex
