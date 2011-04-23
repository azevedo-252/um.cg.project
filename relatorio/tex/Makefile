NAME = relatorio.pdf

SRC= 	main.tex 


all: main.tex
	pdflatex main.tex
	pdflatex main.tex
	mv main.pdf $(NAME)

check:
	aspell -l pt -c -t *.tex

clean:
	cd style && make $@
	rm -f *.toc *.aux *.log *.ind *.idx *.bak *.lof *.lot *.out *~

exec: all
	evince $(NAME) &

.tex:
