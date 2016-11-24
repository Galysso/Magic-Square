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
bool diagonaleGauche(int x, int y, int N);
bool diagonaleDroite(int x, int y, int N);
bool carreTermine(donnees *d);
void nextInd(int N, int *i, int *j);
void prevInd(int N, int *i, int *j);

#include "donnees.c"

#endif //DONNEES_H
