#pragma once

#include "comune.hpp"
#include <cmath>

double modulo_vel(double v[4]);

void calcola_masse(misura* misure, int dim);

/* poiche' questa funzione calcola solo informazioni sulla massa del punto
 * ad ogni istante, devi restituire solo una struct che conterra' media, sigma, max e min
 * della massa, calcolati dalle misure.
 * */
stats calcola_stat_masse(misura* misure, int dim);

/* qui invece devi calcolare le informazioni su tutte e quattro le coordinate della velocita',
 * quindi ti serve restituire un array di stats (Una per ogni coordinata, quindi l'array conterra' quattro stats)
 * */
stats* calcola_stat_velocita(misura* misure, int dim);

double* calcola_posizioni(misura* misure, int dim);
