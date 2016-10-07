#ifndef INCOMPLET_H
#define INCOMPLET_H

#include "donnees.h"

void remplirCarreIncomplet(donnees *d);
void echanger(donnees *d, int i1, int j1, int i2, int j2);
int echangeAleatoire(donnees *d);
bool echangeBulle(donnees *d);
bool echangeTotal(donnees *d);
double score(donnees *d, int i, int j);
double scoreEchange(donnees *d, int i1, int j1, int i2, int j2);
double scoreEchange2(donnees *d, int i1, int j1, int i2, int j2);
void resoudreIncompletAleatoire(donnees *d);
void resoudreIncompletTotal(donnees *d);
void incomplete(int N);

#include "incomplet.c"

#endif //INCOMPLET_H
