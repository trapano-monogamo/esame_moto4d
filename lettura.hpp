#pragma once

#include "comune.hpp"

misura* load_from_file(const char* filename, int& dim);

void output_dati(const char* filename, misura* misure, stats stats_misure, double* posizioni, int dim);
