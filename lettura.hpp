#pragma once

#include "comune.hpp"

misura* load_from_file(const char* filename, int& dim);

int output_dati(const char* filename, misura* misure, double* posizioni, int dim, stats stats_masse, stats stats_vel[4]);
