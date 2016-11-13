#include <iostream>
#include <stdlib.h>
#include "donnees.h"

using namespace std;

donnees *initialiserDonnees(int N) {
	// Initialisation des variables
	donnees *d = new donnees;
	
	d->N = N;							// La taille des côtés du carré
	d->M = (N*(N*N+1))/2;				// La somme de chaque colonne/ligne/diagonale
	d->square = initialiserCarre(N);	// Le carré magique	
	d->col = new int [N];				// Les sommes des colonnes
	d->line = new int [N];				// Les sommes des lignes
	d->diagG = 0;						// La somme de la diagonale gauche
	d->diagD = 0;						// La somme de la diagonale droite
	
	return d;
}

void afficherCarreSimple(donnees *d) {
	int **square = d->square;
	int *col = d->col;
	int *line = d->line;
	int N = d->N;
	
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cout << square[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl << endl;
}

void afficherCarre(donnees *d) {
	int **square = d->square;
	int *col = d->col;
	int *line = d->line;
	int N = d->N;
	
	cout << d->diagG << "\t ";
	for (int i = 0; i < N; ++i) {
		cout << col[i] << "\t";
	}
	cout << d->diagD << endl << endl;
	
	for (int i = 0; i < N; ++i) {
		cout << line[i] << "\t ";
		for (int j = 0; j < N; ++j) {
			cout << square[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

int **initialiserCarre(int N) {
	int **square;
	square = new int * [N];
	for (int i = 0; i < N; ++i) {
		square[i] = new int [N];
	}
	return square;
}

void retirer(donnees *d, int i, int j) {
	int n = d->square[i][j];
	d->square[i][j] = 0;
		
	if (diagonaleGauche(i,j,d->N)) {
		d->diagG = d->diagG - n;
	}
	if (diagonaleDroite(i,j,d->N)) {
		d->diagD = d->diagD - n;
	}
	
	d->line[i] = d->line[i] - n;
	d->col[j] = d->col[j] - n;
}

void ajouter(donnees *d, int n, int i, int j) {
	d->square[i][j] = n;
	
	if (diagonaleGauche(i,j,d->N)) {
		d->diagG = d->diagG + n;
	}
	if (diagonaleDroite(i,j,d->N)) {
		d->diagD = d->diagD + n;
	}

	d->line[i] = d->line[i] + n;
	d->col[j] = d->col[j] + n;
}

bool diagonaleGauche(int x, int y, int N) {
	return (x==y);
}

bool diagonaleDroite(int x, int y, int N) {
	return ((x+y) == (N-1));
}

bool carreTermine(donnees *d) {
	int M = d->M;
	int N = d->N;
	int *line = d->line;
	int *col = d->col;
	bool resultat = ((d->diagG == M) && (d->diagD == M));
	int i = 0;	
	
	while ((i < N) && (resultat)) {
		resultat = (resultat && (line[i]==M) && (col[i]==M));
		i = i + 1;
	}
	
	return resultat;
}

void desallouer(donnees *d) {
	int N = d->N;
	int **square = d->square;
	
	delete(d->col);
	delete(d->line);
	
	for (int i = 0; i < N; ++i) {
		delete(square[i]);
	}
}
