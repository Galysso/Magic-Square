#include <iostream>
#include <stdlib.h>

#include "complet.h"
#include "donnees.h"

using namespace std;

// IMPORTANT
// TODO :
// Lorsqu'on remplit une case, on remplit les values[i][j][n] des n que l'on veut filtrer de l'admissible
//	à la valeur indice calculée en fonction de la case qui vient d'être remplie
//	On ne modifie la valeur de values[i][j][n] que si celle-ci est différente de 0
//	OLorsqu'on supprime une case, on remet la valeur à 0 des values[i][j][n]
//	dont la valeur correspond à celle de la case supprimée


// renvoie l'indice de backtrack (un unique indice par case)
int indice(int N, int i, int j) {
	return N*i+j+1;
}

int ***initialiserValues(int N) {
	int ***values;
	values = new int ** [N];
	for (int i = 0; i < N; ++i) {
		values[i] = new int * [N];
		for (int j = 0; j < N; ++j) {
			values[i][j] = new int [N*N+1];
		}
	}
	return values;
}

void afficherValues(int N, int ***values) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cout << i*N+j << ":{";
			for (int n = 1; n <= N*N; ++n) {
				if (values[i][j][n] == 0) {
					cout <<n<<",";
				}
			}
			cout << "}" << endl;
		}
	}
	cout << endl;
	
	for (int n = 1; n <= N*N; ++n) {
					cout <<values[2][2][n]<<",";
			}cout << endl;
}

int nextValue(int N, int ***values, int n, int i, int j) {
	int max = N*N+1;
	n = n+1;
	
	while ((n < max) && (values[i][j][n] != 0)) {
		n = n + 1;
	}
	
	if (n == max) {
		return -1;
	} else {
		return n;
	}
}

void ajouterComplet(donnees *d, int ***values, int n, int i, int j) {
	ajouter(d, n, i, j);
	propagationAjout(d, values, n, i, j);
}

void retirerComplet(donnees *d, int ***values, int i, int j) {
	int n = d->square[i][j];
	retirer(d, i, j);
	propagationRetrait(d->N, values, i, j);
}

void allDiff(int N, int ***values, int n, int i, int j) {
	int ind = indice(N, i, j);
	
	for (i; i < N; ++i) {
		for (j=0; j < N; ++j) {
			if (values[i][j][n] == 0) {
				values[i][j][n] = ind;
			}
		}
	}
}

int minimumResteLigne(int N, int ***values, int i, int j) {
	int somme = 0;
	
	for (j; j < N; ++j) {
		// amélioration ?
		somme = somme + nextValue(N, values, 0, i, j);
	}
	
	return somme;
}

int maximumResteLige(int N, int j) {
	int nsquare = N*N;
	
	// a vérifier (être précis sur les indices)
	return (N-j-1)*nsquare;
}

void propagationDiagonaleDroite(int N, int ***values, int i, int j) {
	// TODO
}

void propagationDiagonaleGauche(int N, int ***values, int i, int j) {
	// TODO
}

void propagationLigne(donnees *d, int ***values, int i, int j) {
	int ind = indice(d->N, i, j);
	
	int N = d->N;
	int nsquare = N*N;
	int M = d->M;
	int nbCases = N-j-1;
	
	//~ cout<<"i:"<<i<<"\tj:"<<j<<endl;
	//~ cout<<"nbCases:"<<nbCases;
	
	if (nbCases > 0) {
		int maxValue = M-d->line[i];
		//~ cout<<"\tmaxValue:"<<maxValue<<endl;
		
		i = i+1;
		
		for (j = 0; j < N; ++j) {
			for (int n = maxValue; n <= nsquare; ++n) {
				if (values[i][j][n] == 0) {
					//~ cout << "EFFICACITE : "<<n << endl;
					values[i][j][n] = ind;
				}
			}
		}
	}
	//~ cout << endl << endl;
}

void propagationColonne(int N, int ***values, int i, int j) {
	// TODO
}

void propagationAjout(donnees *d, int ***values, int n, int i, int j) {
	allDiff(d->N, values, n, i, j);
	propagationLigne(d, values, i, j);
}

void propagationRetrait(int N, int ***values, int i, int j) {
	int ind = indice(N, i, j);
	int max = N*N;
	
	for (i; i < N; ++i) {
		for (j=0; j < N; ++j) {
			for (int n = 1; n <= max; ++n) {
				if (values[i][j][n] == ind) {
					values[i][j][n] = 0;
				}
			}
		}
	}
}

void bonCarreTrois(donnees *d, int ***values) {
	int N = d->N;
	
	ajouterComplet(d,values,6,0,0);
	afficherValues(N, values);
	ajouterComplet(d,values,1,0,1);
	afficherValues(N, values);
	ajouterComplet(d,values,8,0,2);
	afficherValues(N, values);
	ajouterComplet(d,values,7,1,0);
	afficherValues(N, values);
	ajouterComplet(d,values,5,1,1);
	afficherValues(N, values);
	ajouterComplet(d,values,3,1,2);
	afficherValues(N, values);
	ajouterComplet(d,values,2,2,0);
	afficherValues(N, values);
	ajouterComplet(d,values,9,2,1);
	afficherValues(N, values);
	ajouterComplet(d,values,4,2,2);
	afficherValues(N, values);
}

void resoudreComplet(donnees *d, int ***values) {
	int c = 0;
	
	bool fini = false;
	int N = d->N;
	int nbCase = N*N;
	int i = 0;			// On se place sur la première case du tableau
	int j = 0;
	int n = 0;
	
	do { c = c + 1;
		if (c%1 == 0) {
			//~ afficherCarreSimple(d);
			//~ afficherValues(N, values);
		}
		n = nextValue(N, values, n, i, j);
		
		if (n != -1) {			// S'il existe une valeur correcte
			retirerComplet(d, values, i, j);
			ajouterComplet(d, values, n, i, j);	// On ajoute la valeur à la case courante

			if (j < N-1) {			// Et on se place sur la case suivante
				j = j + 1;
				n = 0;				// On réinitialise pour la case suivante
			} else if (i < N-1) {
				i = i + 1;
				j = 0;
				n = 0;				// On réinitialise pour la case suivante
			} else if (!carreTermine(d)) {	// Si le carre est rempli et invalide
				retirerComplet(d, values, i, j);				// On retire la dernière case du carré
			} else {						// Sinon si le carré est valide
				fini = true;					// On arrête l'algorithme
			}
		} else {				// Sinon s'il n'existe aucune valeur correcte
			retirerComplet(d, values, i, j);		// Alors on retire la case courante (retirer 0 n'a pas d'effet)
			
			if (j > 0) {			// On se place sur la case précédente
				j = j - 1;
			} else {
				j = N - 1;
				i = i - 1;
			}
			
			n = d->square[i][j];	// Et on récupère la valeur de la case précédente pour la changer
		}
	} while (!fini);
}

void complete(int N) {
	// Initialisation des variables
	donnees *d = initialiserDonnees(N);
	int ***values = initialiserValues(N);
	
	// Resolution
	resoudreComplet(d, values);
	
	// Affichage
	afficherCarreSimple(d);
}
