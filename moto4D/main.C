#include "lib.h"

int main() {

	int dim = righeNelFile();
	if ( dim == -1 ) {
		cout << "Problemi col file di dati!" << endl;
		return 1;
	} 
		
	misura* M = new misura[dim];
	
	ofstream out;
	out.open( "risultati.dat" );
	
	caricaArray( M, dim );
	
	cout << endl << "ARRAY CARICATO" << endl;
	
	cout << "Numero misure caricate: " << dim << endl;
	cout << "Eccone la descrizione:" << endl;
	out << "Numero misure caricate: " << dim << endl;
	out << "Eccone la descrizione:" << endl;
	for ( int i = 0; i < dim; i++ ) {
		stampa( M[i] ); cout << endl;
		stampaFile( out, M[i] ); out << endl;
	}
	
	sort( M, dim );

	cout << "\nMisure ordinate per tempo crescente:" << endl;
	out << "\nMisure ordinate per tempo crescente:" << endl;
	for ( int i = 0; i < dim; i++ ) {
		stampa( M[i] ); cout << endl;
		stampaFile( out, M[i] ); out << endl;
	}
	
	double media = setMassaRetMedia( M, dim );
	double deviaz = dev( M, dim, media );

	cout << "\nDescrizione delle particelle comprensiva della massa:" << endl;
	out << "\nDescrizione delle particelle comprensiva della massa:" << endl;
	for ( int i = 0; i < dim; i++ ) {
		stampa( M[i] ); cout << endl;
		stampaFile( out, M[i] ); out << endl;
	}
	
	cout << "\nMedia delle masse: " << media << "; Deviazione standard delle masse: " << deviaz << endl;
	out << "\nMedia delle masse: " << media << "; Deviazione standard delle masse: " << deviaz << endl;

	cout << "\nValore minimo, medio, massimo di vx: ";
	cout << min( M, dim, 0 ) << ", " << med(  M, dim, 0 ) << ", " << max( M, dim, 0 );
	out << "\nValore minimo, medio, massimo di vx: ";
	out << min( M, dim, 0 ) << ", " << med(  M, dim, 0 ) << ", " << max( M, dim, 0 );

	cout << "\nValore minimo, medio, massimo di vy: "; 
	cout << min( M, dim, 1 ) << ", " << med(  M, dim, 1 ) << ", " << max( M, dim, 1 );
	out << "\nValore minimo, medio, massimo di vy: ";
	out << min( M, dim, 1 ) << ", " << med(  M, dim, 1 ) << ", " << max( M, dim, 1 );

	cout << "\nValore minimo, medio, massimo di vz: "; 
	cout << min( M, dim, 2 ) << ", " << med(  M, dim, 2 ) << ", " << max( M, dim, 2 );
	out << "\nValore minimo, medio, massimo di vz: ";
	out << min( M, dim, 2 ) << ", " << med(  M, dim, 2 ) << ", " << max( M, dim, 2 );

	cout << "\nValore minimo, medio, massimo di vw: ";
	cout << min( M, dim, 3 ) << ", " << med(  M, dim, 3 ) << ", " << max( M, dim, 3 );
	out << "\nValore minimo, medio, massimo di vw: ";
	out << min( M, dim, 3 ) << ", " << med(  M, dim, 3 ) << ", " << max( M, dim, 3 );

	cout << endl << "\nPosizioni (x, y, z, w) ai tempi t = 5, 10, 15:" << endl;
	out << endl << "\nPosizioni (x, y, z, w) ai tempi t = 5, 10, 15:" << endl;

	for ( int i = 0; i < dim; i++ ) {
		if ( M[i].t == 5 || M[i].t == 10 || M[i].t == 15  ) {
			cout << "t = " << M[i].t << ": ";
			cout << "x = " << x( M[i] ) << ", y = " << y( M[i] ) << ", ";
			cout << "z = " << z( M[i] ) << ", w = " << w( M[i] ) << endl; 
			out << "t = " << M[i].t << ": ";
			out << "x = " << x( M[i] ) << ", y = " << y( M[i] ) << ", ";
			out << "z = " << z( M[i] ) << ", w = " << w( M[i] ) << endl; 
		}
	}
	
	out.close();
	return 0;
}
