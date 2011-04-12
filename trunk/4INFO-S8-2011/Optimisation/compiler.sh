#!/bin/sh
pdflatex -shell-escape Optimisation_cours
bibtex main
pdflatex -shell-escape Optimisation_cours
pdflatex -shell-escape Optimisation_cours
rm *.log *.aux *.dvi *.lot *.bit *.idx *.glo *.bbl *.ilg *.toc *.ind *.blg *.out

