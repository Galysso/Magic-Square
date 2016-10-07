#ifndef COMPLET_H
#define COMPLET_H

#include "donnees.h"

int ***initialiserValues(int N);
void afficherValues(int N, int ***values);
int nextValue(int N, int ***values, int n, int i, int j);
void ajouterComplet(donnees *d, int ***values, int n, int i, int j);
void retirerComplet(donnees *d, int ***values, int i, int j);
void propagationAjout(donnees *d, int ***values, int n, int i, int j);
void propagationRetrait(int N, int ***values, int i, int j);
void allDiff(int N, int ***values, int n);
void bonCarreTrois(donnees *d, int ***values);
void resoudreComplet(donnees *d, int ***values);
void complete(int N);

#include "complet.c"

#endif //COMPLET_H
