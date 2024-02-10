#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

struct misura {
	int t;
	double* v; 
	double K;
	double massa;
};

int righeNelFile();
void caricaArray( misura*, int );
void stampa( misura );
void stampaFile( ofstream&, misura );
void swap( misura&, misura& );
void sort( misura*, int );
float massa( misura& );
double setMassaRetMedia( misura*, int );
double dev( misura*, int, double );
double min( misura*, int, int );
double max( misura*, int, int );
double med( misura*, int, int );
double x( misura m );
double y( misura m );
double z( misura m );
double w( misura m );


