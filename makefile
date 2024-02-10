# compila dipende da tutti i file .o che ci sono (*.o vuol dire: qualsiasi file che finisca in ".o")
compila: *.o
	g++ $^ -o a.out

# esegui dipende da compila, che dipende dai file .o
esegui: compila
	./a.out

# ogni file .o dipende dal rispettivo file .cpp (il singolo file che finisce in .o dipende
# dallo stesso file che finisce in .cpp, cioe' il suo codice sorgente)
%.o: %.cpp
	g++ -g -Wall -c $^

# pulisci non dipende da niente, e rimuove i file .o i risultati e l'eseguibile (il trattino davanti ignora l'errore del comando,
# cioe' in questo caso quando provi a rimuovere un file che non esiste
pulisci:
	-rm *.o # rimuove tutti i file che finiscono in .o
	-rm risultati.dat
	-rm a.out


# se vuoi approfondire la differenza tra % e * prova a guardare su internet le varie guide
# sui makefile, ma e' difficile comunque.
# Per quanto ne so io:
# quando vuoi riferirti a piu' file che hanno nomi diversi ma che contengono stessi pattern,
# puoi usare una "match expression", cioe' la parte che non ti interessa viene sostituita da % o *,
# e la parte che vuoi matchare la scrivi completa.
#
# Quindi le due scritture
# 	*.cpp
# 	%.cpp
# significano allo stesso modo "qualsiasi file che finisca in .cpp, e non interessa il nome".
#
# Analogamente la scrittura
# 	calcoli.*
# significa "qualsiasi file che inizi con calcoli. , e non interessa l'estensione".
#
# Ancora analogamente la scrittura:
# 	*abc*
# signifca "qualsiasi file che da qualche parte nel nome contiene abc (cioe' prima ha qualcosa, poi abc, e poi qualcos'altro)"
#
# Negli utlimi due casi non va bene usare il % perche' la differenza tra * e % e' che
# * sta a indicare tutti i file che matchano tutti allo stesso momento (cioe' *.cpp viene
# tradotto nella lista: calcoli.cpp lettura.cpp main.cpp),
# mentre % indica i singoli file che hanno matchato (cioe' %.o viene tradotto allo stessso modo ma non viene costruita
# una lista, invece viene chiamata la regola alla riga 11 una volta per ogni file che matcha)
