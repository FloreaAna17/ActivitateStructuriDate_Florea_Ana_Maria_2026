#include<stdio.h>
#include<malloc.h>
#include<string.h>

struct Telefon {
	int id;
	int RAM;
	char* producator;
	float pret;
	char serie;
};
struct Telefon initializare(int id, int RAM, char* producator, float pret, char serie) {
	struct Telefon t;
	t.id = id;
	t.RAM = RAM;
	t.producator = (char*)malloc((strlen(producator) + 1) * sizeof(char));
	strcpy_s(t.producator, strlen(producator) + 1, producator);
	t.pret = pret;
	t.serie = serie;
	return t;
}

struct Telefon copiazaTelefon(struct Telefon t) {
	struct Telefon telefon = initializare(t.id, t.RAM, t.producator, t.pret, t.serie);
	return telefon;
}

void afisare(struct Telefon t) {
	printf("ID: %d\nRAM: %d\nProducator: %s\nPret: %f\nSerie: %c\n\n", t.id, t.RAM, t.producator, t.pret, t.serie);
}

void afisareVector(struct Telefon* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++) {
		afisare(vector[i]);
	}
}

struct Telefon* copiazaPrimeleNElemente(struct Telefon* vector, int nrElemente, int nrElementeCopiate) {
	if (nrElementeCopiate > nrElemente) {
		nrElementeCopiate = nrElemente;
	}
	struct Telefon* vectorNou = (struct Telefon*)malloc(sizeof(struct Telefon) * nrElementeCopiate);
	for (int i = 0; i < nrElementeCopiate; i++) {
		vectorNou[i] = copiazaTelefon(vector[i]);
	}

	return vectorNou;


}

void dezalocare(struct Telefon** vector, int* nrElemente) {
	for (int i = 0; i < *nrElemente; i++) {
		free((*vector)[i].producator);
		(*vector)[i].producator = NULL;
	}
	free(*vector);
	*vector = NULL;
	*nrElemente = 0;
}

void copiazaTelefoaneScumpe(struct Telefon* vector, char nrElemente, float pretMinim, struct Telefon** vectorNou, int* dimensiune) {
	*dimensiune = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].pret >= pretMinim) {
			(*dimensiune)++;
		}
	}
	if (*dimensiune > 0) {
		*vectorNou = (struct Telefon*)malloc(*dimensiune * sizeof(struct Telefon));
		int j = 0;
		for (int i = 0; i < nrElemente; i++) {
			if (vector[i].pret >= pretMinim) {
				(*vectorNou)[j] = copiazaTelefon(vector[i]);
				j++;
			}
		}
	}
	else { 
		*vectorNou = NULL;
		}
	}
	

struct Telefon getPrimulElementConditionat(struct Telefon* vector, int nrElemente, const char* conditie) {
	for (int i = 0; i < nrElemente; i++) {
		if (strcmp(vector[i].producator, conditie) == 0) {
			return copiazaTelefon(vector[i]);
		}
	}
	return initializare(-1, 0, " ", 0, '0');
}
	


int main() {
	struct Telefon t;
	t = initializare(1, 8, "Samsung", 3000,'A');
	afisare(t);
	int nrTelefoane = 3;
	
	struct Telefon* telefoane = (struct Telefon*)malloc(sizeof(struct Telefon) * nrTelefoane);
	telefoane[0] = initializare(1, 8, "Samsung", 3456, 'A');
	telefoane[1] = initializare(2, 8, "Samsung", 2007, 'S');
	telefoane[2] = copiazaTelefon(t);
	printf("Vectorul initial:\n");
	afisareVector(telefoane, nrTelefoane);

	struct Telefon* vectorNou = NULL;
	int dimensiune = 0;
	copiazaTelefoaneScumpe(telefoane, nrTelefoane, 3100.0, &vectorNou, &dimensiune);

	printf("\nTelefoane mai scumpe de 3100:\n");
	afisareVector(vectorNou, dimensiune);

	dezalocare(&vectorNou, &dimensiune);
	dezalocare(&telefoane, &nrTelefoane);
	free(t.producator);

	return 0;
}