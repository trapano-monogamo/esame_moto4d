#include "lib.h"

int righeNelFile() {
	ifstream in;
	in.open( "data.dat" );
	if ( in.fail() )
		return -1;
	string s;
	int k = 0;
	getline( in, s );
	while ( !in.eof() ) {
		k++;
		getline( in, s );
	}
	in.close();
	return k;
}

void caricaArray( misura* X, int dim ) {
	ifstream in;
	in.open( "data.dat" );
	for ( int i = 0; i < dim; i++ ) {
		in >> X[i].t;
		X[i].v = new double[4];
		for ( int j = 0; j < 4; j++ )
			in >> X[i].v[j];
		in >> X[i].K;
		X[i].massa = 0;
	}
	in.close();
}

void stampa( misura m ) {
	cout << "tempo = " << m.t << "  vx = " << m.v[0] << "  vy = " << m.v[1] << "  vz = " << m.v[2] << "  K = " << m.K << "  massa = " << m.massa;
}

void stampaFile( ofstream& out, misura m ) {
	out << "tempo = " << m.t << "  vx = " << m.v[0] << "  vy = " << m.v[1] << "  vz = " << m.v[2] << "  K = " << m.K << "  massa = " << m.massa;
}

void swap( misura& x, misura& y ) {
	misura t = x;
	x = y;
	y = t;
}

void sort( misura* X, int dim ) {
	for ( int i = 0; i < dim - 1; i++ )
		for ( int j = i + 1; j < dim; j++ ) 
		if ( X[j].t < X[i].t )
			swap( X[i], X[j] );
}

float massa( misura& m ) {
	m.massa = ( 2 * m.K ) / ( pow( m.v[0], 2 ) + pow( m.v[1], 2 ) + pow( m.v[2], 2 ) + pow( m.v[3], 2 ) );
        return m.massa;
}

double setMassaRetMedia( misura* X, int dim ) {
	double m = 0;
	for ( int i = 0; i < dim; i++ )
		m += massa( X[i] );
	return m / dim;
}

double dev( misura* X, int dim, double media ) {
	double d = 0;
	for ( int i = 0; i < dim - 1; i++ ) {
		d += pow( X[i].massa - media, 2 );
	}
	return sqrt( d / dim );
}

double min( misura* X, int dim, int i ) {
	double m = X[0].v[i];
	for ( int j = 1; j < dim; j++ )
		if ( X[j].v[i] < m )
		    m = X[j].v[i];
	return m;
}

double max( misura* X, int dim, int i ) {
	double m = X[0].v[i];
	for ( int j = 1; j < dim; j++ )
		if ( X[j].v[i] > m )
		    m = X[j].v[i];
	return m;
}

double med( misura* X, int dim, int i ) {
	double m = 0;
	for ( int j = 0; j < dim; j++ )
	    m += X[j].v[i];
	return m / dim;
}

double x( misura m ) {
    return m.v[0] * m.t;
}

double y( misura m ) {
    return m.v[1] * m.t + 0.5 * m.t * m.t;
}

double z( misura m ) {
    return m.t * sqrt( m.v[2] );
}

double w( misura m ) {
    return log( m.t ) * m.v[3];
}
