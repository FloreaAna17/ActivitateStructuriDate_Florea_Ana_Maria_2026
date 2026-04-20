#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

struct Carte {
	int id;
	char* titlu;
	int nrPagini;
	float rating;
};
//initiliazare
struct Carte initializare(int id, char* titlu, int nrPagini, float rating) {
	struct Carte c;
	c.id = id;
	c.nrPagini = nrPagini;
	c.rating = rating;

	c.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
	strcpy_s(c.titlu, strlen(titlu) + 1, titlu);
	return c;
}
//afisare carte
void afisare(struct Carte c) {
	printf("%d. Cartea %s are %d pagini si un rating de %.1f\n", c.id, c.titlu, c.nrPagini, c.rating);

}

//afisare vector
void afisareVector(struct Carte* c, int nrCarti) {
	for (int i = 0; i < nrCarti; i++) {
		afisare(c[i]);
	}
}

void copiazaCartiBune(struct Carte* carti, int nrCarti,float ratingMinim,struct Carte** cartiNoi, int* nrCartiCopiate) {
	*nrCartiCopiate = 0;
	for (int i = 0; i < nrCarti; i++) {
		if (carti[i].rating > ratingMinim) {
			(*nrCartiCopiate)++;
		}
	}
	*cartiNoi = (struct Carte*)malloc(sizeof(struct Carte) * (*nrCartiCopiate));
	int n = 0;
	for (int i = 0; i < nrCarti; i++) {
		if (carti[i].rating > ratingMinim) {
			(*cartiNoi)[n] = carti[i];
			(*cartiNoi)[n].titlu = (char*)malloc(sizeof(char) * (strlen(carti[i].titlu) + 1));
			strcpy_s((*cartiNoi)[n].titlu, strlen(carti[i].titlu) + 1, carti[i].titlu);
			n++;
		}
	}
}

void dezalocare(struct Carte** carti, int* nrCarti) {
	for (int i = 0; i < (*nrCarti); i++) {
		if ((*carti)[i].titlu != NULL) {
			free((*carti)[i].titlu);
		}
	}
	free(*carti);
	*carti = NULL;
	*nrCarti = 0;
}

int main() {
	/*struct Carte c;
	c = initializare(1, "Floare albastra", 45, 4.7);
	afisare(c);*/

	int nrCarti = 3;
	struct Carte* carti = (struct Carte*)malloc(sizeof(struct Carte) * nrCarti);
	carti[0] = initializare(1, "Carte 1", 23, 2.7);
	carti[1] = initializare(2, "Carte 2", 56, 7.3);
	carti[2] = initializare(3, "Carte 3", 100, 10);

	afisareVector(carti, nrCarti);

	printf("\nCarti bune:\n");
	struct Carte* cartiNoi = NULL;
	int nrCartiCopiate = 0;
	copiazaCartiBune(carti, 3, 5, &cartiNoi, &nrCartiCopiate);
	afisareVector(cartiNoi, nrCartiCopiate);

	printf("Dupa dezalocare: \n");
	dezalocare(&cartiNoi, &nrCartiCopiate);
	afisareVector(cartiNoi, nrCartiCopiate);
	dezalocare(&carti, &nrCarti);
	afisareVector(carti, nrCarti);
	return 0;
}