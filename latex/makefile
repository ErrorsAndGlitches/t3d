.PHONY : all clean

VPATH = 
SHELL = /bin/bash
#TEXS = $($(notdir $(VPATH)):=.tex)
TEXS = treatment.tex highlvl.tex

all: one

one: t3d.tex $(TEXS)
	echo $(TEXS)
	pdflatex t3d.tex

t3d.pdf : t3d.tex $(TEXS)
	pdflatex t3d.tex
	@if [ $$? -eq 0 ]; 	then pdflatex t3d.tex; \
													 pdflatex t3d.tex; fi # compile 2nd and 3rd time
	# note that the shell commands must all be on the same line
	# if you do not include the @ symbol, make prints the statment

clean: 
	rm -f t3d.{pdf,aux,log,out,toc}
