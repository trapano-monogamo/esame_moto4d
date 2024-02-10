/* 1. comune.hpp contiene le due struct che ho usato, e l'ho chiamato cosi' perche' tutti i file include comune.hpp avendo
 *    bisogno delle struct in esso definite.
 * 2. lettura.hpp contiene le funzioni per leggere i file di dati e scrivere il file dei risultati
 * 3. calcoli.hpp contiene tutte le altre funzioni usate per... fare calcoli.
 *
 * E' bene (fino a un certo punto), mano a mano che si va avanti, separare il codice in piu' file per avere una struttura piu' modulare
 * e facile da organizzare, leggere e correggere. Questo non e' molto il caso in cui dividere i file e' utile, ma hey, bisogna esercitarsi.
 * In c++ inoltre si usa separare le function declaration e le function definition, le prime negli header file (.hpp) e le seconde nei
 * file di codice (.cpp)
 *
 * Negli #include non c'e' differenza tra "" e <>, io ho letto che per convenzione <> si usa per le librerie esterne e "" per gli header
 * locali che hai scritto tu.
 * */

#include "comune.hpp"
#include "lettura.hpp"
#include "calcoli.hpp"

using namespace std;


/* questa e' la funzione che mi sono scritto da portare all'esame. But fear not,
 * for I am by your side in your quest to immaculate data analysis programming.
 * Questo commento l'ho scritto per ultimo... sto perdendo la mia sanita' mentale (trenord
 * mi ha ridotto cosi').
 * Il motivo per cui ho scritto cosi' questa funzione e' che per portarla all'esame volevo che fosse una funzione che potessi
 * utilizzare in modo molto elastico che funzionasse sempre.
 * La scrittura template<typename T> indica solo che T puo' essere qualsiasi tipo, e quindi l'argomento
 * della funzione T* array potrebbe essere un array (di nome array, che originalita') di int, float, misura, quello che vuoi.
 * bool (*pred)(T&,T&) e' la parte piu' difficile: e' un argomento (che ho chiamato pred) della funzione, ma e' a sua volta una funzione che restituisce
 * bool e accetta due reference a T come argomenti. 
 * Morale della favola: questa funzione e pred_t (che e' la funzione che passo come pred quando chiamo inplace_selection_sort, pred sta per predicato)
 * possono essere scritti, nel caso particolare di questo codice, come:
 *
 * 	void inplace_selection_sort(misura* misure, int n) {
 * 		for (int i=0; i < n; i++) {
 * 			int ptr = i;
 * 			for (int k=ptr+1; k < n; k++) {
 * 				if (misure[ptr].t < misure[k].t)) { // questo e' il predicato
 * 					T temp = misure[ptr];
 * 					misure[ptr] = misure[k];
 * 					misure[k] = temp;
 * 				}
 * 			}
 * 		}
 * 	}
 *
 * pero' cosi' facendo non potrei usare questa funzione per riordinare un generico array usando un predicato arbitrario.
 * */
template<typename T>
void inplace_selection_sort(T* array, int n, bool (*pred)(T&,T&)) {
	for (int i=0; i < n; i++) {
		int ptr = i;
		for (int k=ptr+1; k < n; k++) {
			if (pred(array[ptr], array[k])) {
				T temp = array[ptr];
				array[ptr] = array[k];
				array[k] = temp;
			}
		}
	}
}

bool pred_t(misura& a, misura& b) {
	return b.t < a.t;
}


int main() {
	// cairca le misure
	int dim;
	misura* misure = load_from_file("./moto4D/data.dat", dim);

	// sorting
	inplace_selection_sort(misure, dim, pred_t);

	// calcola tutto il calcolabile
	calcola_masse(misure, dim);
	stats stats_masse = calcola_stat_masse(misure, dim);
	stats* stats_vel = calcola_stat_velocita(misure, dim);
	double* posizioni = calcola_posizioni(misure, dim);

	// scrivi lo scrivibile dove devi
	output_dati("risultati.dat", misure, posizioni, dim, stats_masse, stats_vel);

	/* dato che abbiamo allocato dinamicamente tutti gli array che abbiamo usato, dobbiamo anche
	 * deallocarli. Se non lo facessimo in questo caso non succederebbe nulla, perche' subito dopo
	 * il programma termina l'esecuzione e il sistema operativo si riprende tutta la memoria, ma se
	 * il programma andasse avanti per molto (magari all'infinito perche' e' un programma interattivo
	 * e si chiude solo quando lo dice l'utente) e questi dati non servissero piu', allora sarebbe
	 * importantissimo deallocare la memoria per evitare di occupare memoria preziosa che non serve piu'.
	 * Se hai voglia di approfondire dopo l'esame, leggiti due cose sui memory leaks, che fanno
	 * vedere in che modo e' rischioso non eliminare la memoria quando non e' piu' utilizzata.
	 *
	 * Noi abbiamo sempre allocato memoria dinamicamente per creare degli array, ma in generale gli operatori
	 * new e delete possono essere usati per allocare anche singole variabili, e la sintassi e' cosi':
	 * 	type* var = new type; // alloca una variabile di tipo "type"
	 * 	delete var; // dealloca la memoria puntata da var
	 * 	type* var = new type[N]; // alloca N variabili di tipo "type", cioe' un array
	 * 	delete[] var; // dealloca la memoria puntata da var, ma chiede anche al sistema operativo quanta memoria era stata allocata li'
	 * */
	delete[] misure;
	misure = nullptr;
	delete[] stats_vel;
	stats_vel = nullptr;

	return 0;
}
