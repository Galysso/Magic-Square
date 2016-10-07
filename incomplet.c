#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "incomplet.h"
#include "donnees.h"

void restart(donnees *d) {
	//cout << "restart" << endl;
	
	// initialisation
	int **square = d->square;
	int N = d->N;
	int max = N*N;
	int indMax = max;
	int k = 0;
	int i, j;
	
	int **combi = new int *[max];
	
	d->diagG = 0;
	d->diagD = 0;
	
	for (i = 0; i < N; ++i) {
		d->col[i] = 0;
		d->line[i] = 0;
		for (j = 0; j < N; ++j) {
			combi[k] = new int [2];
			combi[k][0] = i;
			combi[k][1] = j;
			k = k + 1;
		}
	}
	
	
	// Remplissage
	for (int c = 1; c <= max; ++c) {
		k = rand() % indMax;
		i = combi[k][0];
		j = combi[k][1];
		ajouter(d, c, i, j);
		
		
		for (k = k; k < indMax; ++k) {
			combi[k] = combi[k+1];
		}
		
		indMax = indMax - 1;
	}
}

void remplirCarreIncomplet(donnees *d) {
	//int **square = d->square;
	int N = d->N;
	int cpt = 1;
	
	d->diagG = 0;
	d->diagD = 0;
	
	for (int k = 0; k < N; ++k) {
		d->col[k] = 0;
		d->line[k] = 0;
	}
	
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			//square[i][j] = cpt;
			ajouter(d, cpt, i, j);
			cpt = cpt + 1;
		}
	}
}

void echanger(donnees *d, int i1, int j1, int i2, int j2) {
	int **square = d->square;
	int val = square[i1][j1];
	
	//cout << "i2 : " << i2 << "\tj2 : " << j2 << endl;
	
	/*square[i1][j1] = square[i2][j2];
	square[i2][j2] = val;*/
	
	retirer(d, i1, j1);
	ajouter(d, square[i2][j2], i1, j1);
	
	retirer(d, i2, j2);
	ajouter(d, val, i2, j2);
}

void semiRestart(donnees *d) {
	int k = 0;
	int N = d->N;
	int max = N*N;
	bool fini = false;
	int i1, j1, i2, j2;
	
	while (k < max) {
		i1 = rand() % N;
		j1 = rand() % N;
		i2 = rand() % N;
		j2 = rand() % N;
		echanger(d, i1, j1, i2, j2);
		k = k + 1;
	}
}

int echangeAleatoire(donnees *d) {
	int k = 0;
	int N = d->N;
	int max = d->N*d->N;
	bool fini = false;
	int i1, j1, i2, j2;
	
	while ((!fini) && (k < max)) {
		i1 = rand() % N;
		j1 = rand() % N;
		i2 = rand() % N;
		j2 = rand() % N;
		
		if (scoreEchange(d, i1, j1, i2, j2) < 0) {
			fini = true;
			echanger(d, i1, j1, i2, j2);
		} else {
			k = k + 1;
		}
	}
	
	return k;
}

bool echangeBulle(donnees *d) {
	int N = d->N;
	int c = 0;
	int i2, j2;
	i2 = 0;
	j2 = 0;
	
	for (int i1 = 0; i1 < N; ++i1) {
		for (int j1 = 0; j1 < N; ++j1) {
			if (scoreEchange(d, i1, j1, i2, j2) < 0) {
				echanger(d, i1, j1, i2, j2);
				c = c + 1;
			}
			j2 = j1;
		}
		i2 = i1;
	}
	
	return c;
}

bool echangeTotal(donnees *d) {
	int N = d->N;
	int c = 0;
	
	for (int i1 = 0; i1 < N; ++i1) {
		for (int j1 = 0; j1 < N; ++j1) {
			for (int i2 = 0; i2 < N; ++i2) {
				for (int j2 = 0; j2 < N; ++j2) {
					if (scoreEchange(d, i1, j1, i2, j2) < 0) {
						echanger(d, i1, j1, i2, j2);
						c = c + 1;
					}
				}
			}
		}
	}
	
	return c;
}

// Le score indique l'écart moyen avec le nombre magique M
double score(donnees *d, int i, int j) {
	double score = 0;
	int N = d->N;
	int M = d->M;
	int cpt = 2;
	
	if (diagonaleGauche(i, j, N)) {
		score = score + d->diagG;
		cpt = cpt + 1;
	}
	if (diagonaleDroite(i, j, N)) {
		score = score + d->diagD;
		cpt = cpt + 1;
	}
	score = score + d->col[j];
	score = score + d->line[i];
	
	score = score/cpt - M;
	
	if (score < 0) {
		return -score;
	} else {
		return score;
	}
}

double scoreEchange(donnees *d, int i1, int j1, int i2, int j2) {
	int N = d->N;
	int M = d->M;
	int **square = d->square;
	int score1, score2, futurScore1, futurScore2;
	int cpt1 = 2;
	int cpt2 = 2;
	
	int val1 = square[i1][j1];
	int val2 = square[i2][j2];
	
	int diff = val1 - val2;
	
	score1 = 0;
	score2 = 0;
	futurScore1 = 0;
	futurScore2 = 0;
	
	if (diagonaleGauche(i1, j1, N) && !diagonaleGauche(i2, j2, N)) {
		score1 = score1 + d->diagG;
		cpt1 = cpt1 + 1;
	} else if (diagonaleGauche(i2, j2, N) && !diagonaleGauche(i1, j1, N)) {
		score2 = score2 + d->diagG;
		cpt2 = cpt2 + 1;
	}
	
	if (diagonaleDroite(i1, j1, N) && !diagonaleDroite(i2, j2, N)) {
		score1 = score1 + d->diagD;
		cpt1 = cpt1 + 1;
	} else if (diagonaleDroite(i2, j2, N) && !diagonaleDroite(i1, j1, N)) {
		score2 = score2 + d->diagD;
		cpt2 = cpt2 + 1;
	}	
	
	score1 = score1 + d->col[j1];
	score1 = score1 + d->line[i1];
	
	score2 = score2 + d->col[j2];
	score2 = score2 + d->line[i2];
	
	futurScore1 = score1 - cpt1*diff;
	futurScore2 = score2 + cpt2*diff;
	
	score1 = score1 - cpt1*M;
	score2 = score2 - cpt2*M;
	
	futurScore1 = futurScore1 - cpt1*M;
	futurScore2 = futurScore2 - cpt2*M;
	
	if (score1 < 0) {
		score1 = -score1;
	}
	if (score2 < 0) {
		score2 = -score2;
	}
	if (futurScore1 < 0) {
		futurScore1 = -futurScore1;
	}
	if (futurScore2 < 0) {
		futurScore2 = -futurScore2;
	}
	
	if (cpt1 == 2) {
		score1 = score1*6;
		futurScore1 = futurScore1*6;
	} else if (cpt1 == 3) {
		score1 = score1*4;
		futurScore1 = futurScore1*4;
	} else if (cpt1 == 4) {
		score1 = score1*3;
		futurScore1 = futurScore1*3;
	}
	
	if (cpt2 == 2) {
		score2 = score2*6;
		futurScore2 = futurScore2*6;
	} else if (cpt2 == 3) {
		score2 = score2*4;
		futurScore2 = futurScore2*4;
	} else if (cpt2 == 4) {
		score2 = score2*3;
		futurScore2 = futurScore2*3;
	}
		
	return (futurScore2 + futurScore1 - score2 - score1);
}

void resoudreIncompletAleatoire(donnees *d) {
	
	double echangesTot = 0;
	double echanges = 0;
	double iterations = 1;
	double restarts = 1;
	
	while (!carreTermine(d)) {//cout << "iteration" << endl;
		
		//~ cout << "-------------------------------------------" << endl;
		//~ afficherCarre(d);
		
		echanges = echangeAleatoire(d);
		echangesTot = echangesTot + echanges;
		iterations = iterations + 1;
		
		if (echanges == 0) {
			restarts = restarts + 0;
			restart(d);
		}
	}
}

void resoudreIncompletTotal(donnees *d) {
	double echangesTot = 0;
	double echanges = 0;
	double iterations = 1;
	double restarts = 1;
	
	while (!carreTermine(d)) {
		echanges = echangeTotal(d);
		echangesTot = echangesTot + echanges;
		iterations = iterations + 1;
		
		if (echanges == 0) {
			restarts = restarts + 1;
			restart(d);
		}
	}
}

void resoudreIncompletBulle(donnees *d) {
	double echangesTot = 0;
	double echanges = 0;
	double iterations = 1;
	double restarts = 1;
	
	while (!carreTermine(d)) {
		echanges = echangeBulle(d);
		echangesTot = echangesTot + echanges;
		iterations = iterations + 1;
		
		if (echanges == 0) {
			restarts = restarts + 0;
			restart(d);
		} else {
			//afficherCarre(d);
		}
	}
}

void incompleteBulle(int N) {	
	// Initialisation des variables
	donnees *d = initialiserDonnees(N);
	//~ remplirCarreIncomplet(d);
	restart(d);
	afficherCarre(d);
	
	// Resolution
	//~ resoudreIncompletAleatoire(d);
	
	resoudreIncompletBulle(d);
	
	// Affichage
	afficherCarre(d);
}

void incompleteAleatoire(int N) {
	srand(time(NULL));
	
	// Initialisation des variables
	donnees *d = initialiserDonnees(N);
	//~ remplirCarreIncomplet(d);
	restart(d);
	afficherCarre(d);
	
	// Resolution
	//~ resoudreIncompletAleatoire(d);
	
	resoudreIncompletAleatoire(d);
	
	// Affichage
	afficherCarre(d);
}

void incompleteTotal(int N) {
	// Initialisation des variables
	donnees *d = initialiserDonnees(N);
	//~ remplirCarreIncomplet(d);
	restart(d);
	afficherCarre(d);
	
	// Resolution
	
	resoudreIncompletTotal(d);
	
	// Affichage
	afficherCarre(d);
}
