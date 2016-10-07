#ifndef DONNEES_H
#define DONNEES_H

typedef struct donnees {
	int N;
	int M;
	int **square;
	int ***values;
	int *col;
	int *line;
	int diagG;
	int diagD;
} donnees;

void afficherCarreSimple(donnees *d);
void afficherCarre(donnees *d);
int **initialiserCarre(int N);
void retirer(donnees *d, int i, int j);
void ajouter(donnees *d, int n, int i, int j);
int diagonaleGauche(int x, int y, int N);
int diagonaleDroite(int x, int y, int N);
bool carreTermine(donnees *d);

#include "donnees.c"

#endif //DONNEES_H
