PDFLATEX_FLAGS = -interaction=nonstopmode

#Incluimos main.pdf para poder forzar la compilación aun no habiendo cambios (chapuza xD)
.PHONY: all, clean, pdf, main.pdf

all: pdf

pdf: main.pdf

main.pdf : 
	#Triple compilación para actualizar las referencias
	pdflatex $(PDFLATEX_FLAGS) main.tex
	bibtex main.aux
	pdflatex $(PDFLATEX_FLAGS) main.tex
	pdflatex $(PDFLATEX_FLAGS) main.tex

clean:
	@-rm -v *.log 2>/dev/null; true
	@-rm -v *.aux 2>/dev/null; true
	@-rm -v *.pdf 2>/dev/null; true
	@-rm -v *.dvi 2>/dev/null; true
	@-rm -v *.toc 2>/dev/null; true
