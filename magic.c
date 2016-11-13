#include <iostream>
#include <time.h>

#include "complet.h"
#include "incomplet.h"

using namespace std;

int main() {
	srand(time(NULL));
	clock_t debut, fin;
	
	int N;
	cout << "Taille du carré : ";
	//~ cin >> N;
	
	
	cout << "Lancement algorithme complet" << endl;
	debut = clock();
	complete(6);
	fin = clock();
	cout << "Résolution en " << (fin-debut)*1000/CLOCKS_PER_SEC << " millisecondes" << endl;
	
	//~ cout << "Lancement algorithme incomplet" << endl;
	//~ debut = clock();
	//~ incompleteTotal(N);
	//~ fin = clock();
	//~ cout << "Résolution en " << (fin-debut)*1000/CLOCKS_PER_SEC << " millisecondes" << endl;
	
	return 0;
}
