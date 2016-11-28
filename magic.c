#include <iostream>
#include <time.h>
#include <string>

#include "complet.h"
#include "incomplet.h"

using namespace std;

int main() {
	srand(time(NULL));
	clock_t debut, fin;
	
	int N, delai;
	bool complet, refaire;
	string reponse;
	
	do {
		do {
			cout << "Souhaitez-vous utiliser le solveur complet ou incomplet ? C\\I : ";
			cin >> reponse;
		} while (reponse.compare("C")!=0 && reponse.compare("c")!=0 && reponse.compare("I")!=0 && reponse.compare("i")!=0);
		
		if (reponse.compare("C")!=0 || reponse.compare("c")!=0) {
			complet = true;
		}
		
		cout << "Taille du carré : ";
		cin >> N;
		cout << endl;
		
		if (complet) {
			cout << "Lancement algorithme complet" << endl;
			debut = clock();
			complete(N);
			fin = clock();
			cout << "Résolution en " << (fin-debut)*1000/CLOCKS_PER_SEC << " millisecondes" << endl;
		} else {
			cout << "Lancement algorithme incomplet" << endl;
			debut = clock();
			incompleteTotal(N);
			fin = clock();
			cout << "Résolution en " << (fin-debut)*1000/CLOCKS_PER_SEC << " millisecondes" << endl;
		}
		
		do {
			cout << "Souhaitez-vous refaire un essai ? O\\N : ";
			cin >> reponse;
		} while (reponse.compare("O")!=0 && reponse.compare("o")!=0 && reponse.compare("N")!=0 && reponse.compare("n")!=0);
		
		if (reponse.compare("O") || reponse.compare("o")) {
			refaire = true;
		} else {
			refaire = false;
		}

	} while (refaire);
	
	return 0;
}
