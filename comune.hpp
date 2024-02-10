#pragma once

struct misura {
	int t;			// istante di misurazione
	double v[4];	// componenti della velocita':   v = (vx,vy,vz,vw)
	double K;		// energia cinetica totale
	double massa;	// massa del punto
};

// questa struct contiene parametri statistici per una quantita' sola.
struct stats {
	double media;
	double devstd;
	double max;
	double min;
};
