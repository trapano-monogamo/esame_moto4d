# main.C contiene il sorgente del programma principale e include lib.h
# lib.C contiene il sorgente della libreria e include lib.h
# l'eseguibile viene chiamato main.x

# il comando 'make compila' lancia la compilazione
# il comando 'make esegui' lancia il programma
# il comando 'make clean' cancella tutti i file con estensione .o

# Attenzione all'uso del <TAB> per indentare i comandi di ogni punto

main.x: main.o lib.o
	g++ -o main.x main.o lib.o

main.o: main.C lib.h
	g++ -c main.C

lib.o: lib.C lib.h
	g++ -c lib.C

compila: main.x

esegui:
	./main.x

clean:
	rm *.o
