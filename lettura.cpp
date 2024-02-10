#include "lettura.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

misura* load_from_file(const char* filename, int& dim) {
	// apri filename
	ifstream dati;
	dati.open(filename);

	/* conta il numero di righe, che serve per sapere quanto sara' lungo l'array di misure.
	 * Questo ciclo while e' equivalente a
	 *
	 * 	while(!dati.eof()) {
	 * 		dati >> ...;
	 * 		dim++;
	 * 	}
	 *
	 * ma il vantaggio e' che non dobbiamo definire 6 variabili ausiliarie per leggere un'intera riga,
	 * invece, abbiamo bisogno solo di una stringa (std::string) da passare alla funzione getline(),
	 * che legge l'intera riga in una stringa senza interpretare nessun dato (a differenza di >> che cerca di interpretare
	 * un pezzo di stringa a seconda del tipo di variabile che ci metti dopo).
	 *
	 * potremmo sfruttare questa funzione getline() per evitare di rileggere il file, scrivendolo tutto
	 * riga per riga in una stringa, ma questo renderebbe un po' piu' compilacata la scrittura dei dati
	 * nell'array.
	 * */
	dim = 0; // dim e' il parametro che vogliamo modificare
	string riga;
	while(getline(dati,riga)) {
		dim++;
	}
	// chiudi e riapri perche' siamo arrivati alla fine del file ma dobbiamo ancora leggere effettivamente i dati
	dati.close();
	dati.open(filename);

	// alloca l'array e popolalo con i dati che ora possiamo leggere dal file.
	misura* misure = new misura[dim];
	for (int i = 0; i < dim; i++) {
		dati >> misure[i].t >> misure[i].v[0] >> misure[i].v[1] >> misure[i].v[2] >> misure[i].v[3] >> misure[i].K;
		// se vuoi controllare i dati:
		// cout << misure[i].t << ", {"
		// 	<< misure[i].v[0] << "," << misure[i].v[1] << "," << misure[i].v[2] << "," << misure[i].v[3] << "}, "
		// 	<< misure[i].K << ", "
		// 	<< misure[i].massa << ", "
		// 	<< endl;
	}

	// e' buona pratica chiudere sempre i file quando non li usi piu'.
	dati.close();

	return misure;
}

/* visto che per l'esame chiedono di stampare i risultati su un file E sul terminale, ho deciso
 * di fare entrambi allo stesso momento e in una botta sola. All'esame ti consiglio di fare queste due cose
 * in momenti separati, quindi al posto di ss metti f, e poi ripeti la stessa cosa ma al posto di ss metti cout.
 * In sostanza quello che ho fatto qui e' creare uno stringstream, che e' molto simile, come struttura, ad un file,
 * e infatti posso usare gli operatori << e >> per leggere e scrivere sullo stream. Una volta scritto sullo stringstream,
 * riscrivo il suo contentuo su un file e sul cout.
 * */
void output_dati(const char* filename, misura* misure, double* posizioni, int dim, stats stats_masse, stats stats_vel[4]) {
	ofstream f;
	f.open(filename);
	stringstream ss;

	for (int i=0; i<dim; i++) {
		ss << "t: " << misure[i].t << "\nvelocita': {"
			<< misure[i].v[0] << "," << misure[i].v[1] << "," << misure[i].v[2] << "," << misure[i].v[3] << "}\nK: "
			<< misure[i].K << "\nmassa: "
			<< misure[i].massa << "\nposizione: {"
			<< posizioni[4*i + 0] << "," << posizioni[4*i + 1] << "," << posizioni[4*i + 2] << "," << posizioni[4*i + 3] << "}, "
			<< endl << endl;
	}
	ss << "media masse: " << stats_masse.media << endl << "sigma masse: " << stats_masse.devstd << endl << endl;
	for (int i=0; i<4; i++) {
		ss << "velocita': componente " << i << endl
			<< "media velocita': " << stats_vel[i].media << endl
			<< "sigma velocita': " << stats_vel[i].devstd << endl
			<< "max velocita': " << stats_vel[i].max << endl
			<< "min velocita': " << stats_vel[i].min << endl << endl;;
	}

	/* non preoccuparti troppo neanche di questo loop. E' a meta' tra un ciclo while e un ciclo for e
	 * si usa con gli iteratori (std::vector, std::stringstream, std::string, std::array, std::unordered_map, ...),
	 * e in pratica legge uno a uno gli elementi dell'iteratore anziche' incrementare un indice e leggere manualmente
	 * gli elemente dell'iteratore attraverso quell'indice.
	 * */
	for (auto& s : ss.str()) {
		f << s;
		cout << s;
	}

	// e' buona pratica chiudere sempre i file quando non li usi piu'.
	f.close();
}
