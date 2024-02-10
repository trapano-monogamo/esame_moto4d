#include "calcoli.hpp"

double modulo_vel(double v[4]) {
	return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2] + v[3]*v[3]);
}

void calcola_masse(misura* misure, int dim) {
	for (int i=0; i<dim; i++) {
		misure[i].massa = (2 * misure[i].K) / pow(modulo_vel(misure[i].v),2);
	}
}

stats calcola_stat_masse(misura* misure, int dim) {
	/* variabili usate per accumulare una certa quantita' per fare la sommatroia.
	 * di solito vengono chiamate "accumulatore" (media_accumulatore e devstd_accumulatore)
	 * */
	double m_acc = 0;
	double ds_acc = 0;

	for (int i=0; i<dim; i++) {
		m_acc += misure[i].massa;
	}
	double media = m_acc / dim;

	for (int i=0; i<dim; i++) {
		ds_acc += pow(misure[i].massa - media, 2);
	}
	double devstd = sqrt(ds_acc / (dim + 1));

	/* restituisci una struct, inizializzandola sul momento anziche' creare una variabile, e la sintassi
	 * per inizializzare una struct e' questa:
	 * 	(tipo){ campo1, campo2, campo3, ... }
	 * dove "tipo" e' la struct che vuoi creare, e i campi sono i dati che vuoi che la struct che stai creando
	 * contenga. Mettere (tipo) serve per dire al compilatore che struct stai creando (si chiama casting, e quando
	 * il compilatore non puo' dedurre da solo che tipo sta creando, c'e' bisogno di specificarlo, come in questo caso.
	 * Ci sono alcune regole per capire quando puo' avvenire implicit casting e quando serve explicit casting)
	 * */
	return (stats){ media, devstd }; // max e min non richiesti, non e' necessario includerli
}

stats* calcola_stat_velocita(misura* misure, int dim) {
	// stesso ragionamento di prima, ma questa volta una quantita' per ogni coordinata
	double m_acc[4]{ };
	double ds_acc[4]{ };
	double max[4]{ };
	double min[4]{ };

	for (int i=0; i<dim; i++) {
		m_acc[0] += misure[i].v[0];
		m_acc[1] += misure[i].v[1];
		m_acc[2] += misure[i].v[2];
		m_acc[3] += misure[i].v[3];

		if (misure[i].v[0] >= max[0]) max[0] = misure[i].v[0];
		if (misure[i].v[1] >= max[1]) max[1] = misure[i].v[1];
		if (misure[i].v[2] >= max[2]) max[2] = misure[i].v[2];
		if (misure[i].v[3] >= max[3]) max[3] = misure[i].v[3];

		if (misure[i].v[0] <= min[0]) min[0] = misure[i].v[0];
		if (misure[i].v[1] <= min[1]) min[1] = misure[i].v[1];
		if (misure[i].v[2] <= min[2]) min[2] = misure[i].v[2];
		if (misure[i].v[3] <= min[3]) min[3] = misure[i].v[3];
	}
	double media[4] = { m_acc[0]/dim, m_acc[1]/dim, m_acc[2]/dim, m_acc[3]/dim };

	for (int i=0; i<dim; i++) {
		ds_acc[0] += pow(misure[i].v[0] - media[0], 2);
		ds_acc[1] += pow(misure[i].v[1] - media[1], 2);
		ds_acc[2] += pow(misure[i].v[2] - media[2], 2);
		ds_acc[3] += pow(misure[i].v[3] - media[3], 2);
	}
	double devstd[4] = { sqrt(ds_acc[0] / (dim + 1)), sqrt(ds_acc[1] / (dim + 1)), sqrt(ds_acc[2] / (dim + 1)), sqrt(ds_acc[3] / (dim + 1)) };

	/* MALE MALE MALISSIMO, NON FARLO MAI PER L'AMOR DEL CIELO!
	 * Il problema e' che tu sai che hai bisogno solo di quattro elementi nell'array, ma se creassi un array
	 * statico e provassi a restituirlo, restituiesti un puntatore valido ad una memoria che pero' verrebbe cancellata
	 * subito dopo l'esecuzione della funzione. Ricordati che gli array statici, come anche le variabili normali,
	 * vivono sullo stack, e quando lo stack frame in cui vivono viene eliminato (la funzione che le crea finisce l'esecuzione)
	 * anche la memoria che occupano viene eliminata.
	 * E quindi in questo caso uso un array dinamico, ma il motivo per cui questa e' una pessima decisione e' che poi qualcuno
	 * deve liberare la memoria che ho allocato in questa funzione, ma quel qualcuno potrebbe non sapere che ho allocato questo array
	 * (magari questa potrebbe essere la funzione di una libreria molto complicata).
	 * L'alternativa sarebbe usare uno std::vector, o ancora meglio uno std::array (il secondo e' piu' efficiente per gestire
	 * memoria statica), che funzionerebbe come una struct:
	 * quando restituisci una struct o una variabile normale, il valore che restituisci viene copiato al di fuori dello stack frame;
	 * quindi se stai restituiendo un puntatore, il puntatore viene copiato (restituisce l'indirizzo di memoria giusto), ma la memoria
	 * a cui punta non viene copiata (e' un concetto simile alla differenza tra shallow copy e deep copy, se vuoi approfondire gia' adesso).
	 *
	 * anche restituire gli array allocati dinamicamente con i dati caricati dai file e' una brutta idea.
	 * */
	stats* s = new stats[4]{
		(stats){ media[0], devstd[0], max[0], min[0] },
		(stats){ media[1], devstd[1], max[1], min[1] },
		(stats){ media[2], devstd[2], max[2], min[2] },
		(stats){ media[3], devstd[3], max[3], min[3] }
	};
	return s;
}

double* calcola_posizioni(misura* misure, int dim) {
	/* odio personale (ma giustificato, infatti li si vedono moooolto raramente anche nei codici grossi)
	 * per gli array multidimensionali.
	 * Invece di creare un array che ha come elementi array di 4 elementi, creo un array solo con
	 * una dimensione 4 volte maggiore per accomodare 4 coordinate per ogni misura.
	 * In memoria l'array diventa:
	 *	 +----------------------------------------
	 *	 |a0 a1 a2 a3 b0 b1 b2 b3 c0 c1 c2 c3 ...
	 *	 +----------------------------------------
	 * che possiamo rappresentare come una matrice:
	 *	 +-----------+
	 *	 |a0 a1 a2 a3|
	 *	 +-----------+
	 *	 +-----------+
	 *	 |b0 b1 b2 b3|
	 *	 +-----------+
	 *	 +-----------+
	 *	 |c0 c1 c2 c3|
	 *	 +-----------+
	 *	 ...
	 * e possiamo accedere ai singoli elementi con la formula:
	 *   x * w + y
	 * dove x e y sono le "coordinate" (x colonna e y riga) di un elemento nella matrice,
	 * e w e' la lunghezza di ogni riga.
	 * (Ti sposti di w elementi per ogni riga, piu' il numero della colonna).
	 * Se lasci sedimentare questa formula diventa tutto
	 * molto piu' facile rispetto ad usare un array multidimensionale (sbagliare ad allocarli e usarli e' facilissimo).
	 * */
	double* pos = new double[dim * 4];

	for (int i=0; i<dim; i++) {
		pos[4*i + 0] = misure[i].v[0] * misure[i].t;
		pos[4*i + 1] = misure[i].v[1] * misure[i].t + 0.5 * pow(misure[i].t,2);
		pos[4*i + 2] = sqrt(misure[i].v[2]) * misure[i].t;
		pos[4*i + 3] = misure[i].v[3] * log(misure[i].t);
	}

	return pos;
}
