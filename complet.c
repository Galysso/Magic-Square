#include <iostream>
#include <stdlib.h>
#include <time.h>

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

int randValue(int N, int ***values, int i, int j) {
	int max = N*N;
	int n = 1 + rand() % max;
	
	while ((n <= max) && (values[i][j][n] != 0)) {
		n = n + 1;
	}
	if (n > max) {
		n = 1;
		while ((n <= max) && (values[i][j][n] != 0)) {
			n = n + 1;
		}
	}
	
	if (n > max) {
		n = -1;
	}
	
	return n;
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

int lastValue(int N, int ***values, int i, int j) {
	int n = N*N;
	
	while ((n > 0) && (values[i][j][n] != 0)) {
		n = n - 1;
	}
	
	return n;
}

void ajouterComplet(donnees *d, int ***values, int n, int i, int j) {
	ajouter(d, n, i, j);
	propagationAjout(d, values, n, i, j);
}

void retirerComplet(donnees *d, int ***values, int i, int j) {
	//~ int n = d->square[i][j];
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

int minimumResteColonne(int N, int ***values, int i, int j) {
	int n;
	int somme = 0;
	
	for (i=i+1; i < N; ++i) {
		n = nextValue(N, values, 0, i, j);
		if (n > 0) {
			somme = somme + n;
		}
	}
	
	return somme;
}

int maximumResteColonne(int N, int ***values, int i, int j) {
	int n;
	int somme = 0;
	
	for (i=i+1; i < N; ++i) {
		n = lastValue(N, values, i, j);
		if (n != -1) {
			somme = somme + n;
		}
	}
	
	return somme;
}

int minimumResteLigne(int N, int ***values, int i, int j) {
	int n;
	int somme = 0;
	
	for (j=j+1; j < N; ++j) {
		n = nextValue(N, values, 0, i, j);
		if (n != -1) {
			somme = somme + n;
		}
	}
	
	return somme;
}

int maximumResteLigne(int N, int ***values, int i, int j) {
	int n;
	int somme = 0;
	
	for (j=j+1; j < N; ++j) {
		n = lastValue(N, values, i, j);
		if (n != -1) {
			somme = somme + n;
		}
	}
	
	// a vérifier (être précis sur les indices)
	return somme;
}

void propagationLigne(donnees *d, int ***values, int i, int j) {
	int N = d->N;
	int ind = indice(N, i, j);
	int reste = d->M - d->line[i];
	int nbCases = N-j-1;
	int borneInf = reste - N*N*(nbCases-1) - (nbCases*(nbCases+1)/2);
	int borneSup = reste - (nbCases-1)*(nbCases)/2;
	
	for (j=j+1; j < N; ++j) {
		for (int n = borneInf; n > 0; --n) {		// Borne inférieure EXCLUE???? des possibilités ???
			if (values[i][j][n] == 0) {
				values[i][j][n] = ind;
			}
		}
		for (int n = borneSup+1; n <= N*N; ++n) {	// Borne supérieure incluse dans les possibilités
			if (values[i][j][n] == 0) {
				values[i][j][n] = ind;
			}
		}
	}
}

void propagationColonne(donnees *d, int ***values, int i, int j) {
	int N = d->N;
	int ind = indice(N, i, j);
	int reste = d->M - d->col[j];
	int nbCases = N-i-1;
	int borneInf = reste - N*N*(nbCases-1) - (nbCases*(nbCases+1)/2);
	int borneSup = reste - (nbCases-1)*(nbCases)/2;
	
	for (i=i+1; i < N; ++i) {
		for (int n = borneInf; n > 0; --n) {		// Borne inférieure EXCLUE???? des possibilités ???
			if (values[i][j][n] == 0) {
				values[i][j][n] = ind;
			}
		}
		for (int n = borneSup+1; n <= N*N; ++n) {	// Borne supérieure incluse dans les possibilités
			if (values[i][j][n] == 0) {
				values[i][j][n] = ind;
			}
		}
	}
}

void propagationDiagonaleGauche(donnees *d, int ***values, int i, int j) {
	int N = d->N;
	int ind = indice(N, i, j);
	int reste = d->M - d->diagG;
	int nbCases = N-i-1;
	int borneInf = reste - N*N*(nbCases-1) - (nbCases*(nbCases+1)/2);
	int borneSup = reste - (nbCases-1)*(nbCases)/2;
	
	for (i=i+1; i < N; ++i) {
		for (int n = borneInf; n > 0; --n) {		// Borne inférieure EXCLUE???? des possibilités ???
			if (values[i][i][n] == 0) {
				values[i][i][n] = ind;
			}
		}
		for (int n = borneSup+1; n <= N*N; ++n) {	// Borne supérieure incluse dans les possibilités
			if (values[i][i][n] == 0) {
				values[i][i][n] = ind;
			}
		}
	}
}

void propagationDiagonaleDroite(donnees *d, int ***values, int i, int j) {
	int N = d->N;
	int ind = indice(N, i, j);
	int reste = d->M - d->diagD;
	int nbCases = N-i-1;
	int borneInf = reste - N*N*(nbCases-1) - (nbCases*(nbCases+1)/2);
	int borneSup = reste - (nbCases-1)*(nbCases)/2;
	
	for (i=i+1; i < N; ++i) {
		j = N - i - 1;
		for (int n = borneInf; n > 0; --n) {		// Borne inférieure EXCLUE???? des possibilités ???
			if (values[i][j][n] == 0) {
				values[i][j][n] = ind;
			}
		}
		for (int n = borneSup+1; n <= N*N; ++n) {	// Borne supérieure incluse dans les possibilités
			if (values[i][j][n] == 0) {
				values[i][j][n] = ind;
			}
		}
	}
}

//~ void propagationSymetrie(int N, int ***values, int n, int i, int j) {
	//~ int val;
	//~ int nSquare = N*N;
	//~ int ind = indice(N, i, j);
	
	//~ if (i+j == 0) {
		//~ for (val=n-1; val > 0; --val) {
			//~ // A < B
			//~ if (values[0][N-1][val] == 0) {
				//~ values[0][N-1][val] = ind;
			//~ }
			
			//~ // A < C
			//~ if (values[N-1][0][val] == 0) {
				//~ values[N-1][0][val] = ind;
			//~ }
		//~ }
	//~ }
	
	//~ if ((i == 0) && (j == N-1)) {
		//~ for (val=nSquare; val > n; --val) {
			//~ // C < B
			//~ if (values[N-1][0][val] == 0) {
				//~ values[N-1][0][val] = ind;
			//~ }
		//~ }
	//~ }
//~ }

void propagationSymetrie(int N, int ***values, int n, int i, int j) {
	int val;
	int nSquare = N*N;
	int ind = indice(N, i, j);
	
	if (i+j == 0) {
		for (val=n-1; val > 0; --val) {
			// A < B
			if (values[0][1][val] == 0) {
				values[0][1][val] = ind;
			}
			
			// A < C
			if (values[1][0][val] == 0) {
				values[1][0][val] = ind;
			}
		}
	}
	
	if ((i == 0) && (j == 1)) {
		for (val=nSquare; val > n; --val) {
			// C < B
			if (values[1][0][val] == 0) {
				values[1][0][val] = ind;
			}
		}
	}
}

void propagationAjout(donnees *d, int ***values, int n, int i, int j) {
	int N = d->N;
	allDiff(N, values, n, i, j);
	propagationLigne(d, values, i, j);
	propagationColonne(d, values, i, j);
	if (diagonaleGauche(i, j, N)) {
		propagationDiagonaleGauche(d, values, i, j);
	}
	if (diagonaleDroite(i, j, N)) {
		propagationDiagonaleDroite(d, values, i, j);
	}
	propagationSymetrie(N, values, n, i, j);
	
	values[i][j][n] = -1;
}

void propagationRetrait(int N, int ***values, int i, int j) {
	//~ cout << "i="<<i<<" j="<<j<<endl;
	int ind = indice(N, i, j);
	int max = N*N;
	int x, y, n;
	
	for (x = i; x < N; ++x) {
		for (y=0; y < N; ++y) {
			for (n = 1; n <= max; ++n) {
				if (values[x][y][n] == ind) {
					values[x][y][n] = 0;
				}
			}
		}
	}
	
	
	if (i+j < 2*(N-1)) {
		if (j < N-1) {
			x = i;
			y = j + 1;
			//~ cout << "x="<<x<<" y="<<y<<" n="<<n<<endl;
		} else if (i < N-1) {
			x = i+1;
			y = 0;
		}
		for (n = 1; n <= max; ++n) {
			if (values[x][y][n] == -1) {
				values[x][y][n] = 0;
			}
		}
	}
}

/* Plutot qu'un vrai aléatoire, choisir le départ de manière aléatoire et prendre la première valeur correcte à partir de ce point de départ*/

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
		if (c%10000000 == 0) {
			afficherCarre(d);
			//~ afficherValues(N, values);
		}
		//~ n = nextValue(N, values, n, i, j);
		n = randValue(N, values, i, j);
		
		if (n != -1) {			// S'il existe une valeur correcte
			retirerComplet(d, values, i, j);
			ajouterComplet(d, values, n, i, j);	// On ajoute la valeur à la case courante			

			if (j < N-1) {			// Et on se place sur la case suivante
				j = j + 1;
				n = 0;				// On réinitialise pour la case suivante
			} else if (i < N-1) {
				i = i + 1;
				j = 0;
				n = 0;		
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
