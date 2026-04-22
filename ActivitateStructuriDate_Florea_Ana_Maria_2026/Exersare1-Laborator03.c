#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraAngajat {
	int id;
	char* nume;
	char* departament;
	float salariu;
	char gen;
};
typedef struct StructuraAngajat Angajat;

void afisareAngajat(Angajat a) {
	printf("%d. Anagajatul: %s din departamentul: %s are un salariul de :%.2f. (%c)\n", a.id, a.nume, a.departament, a.salariu, a.gen);
 }

void afisareVectorAngajat(Angajat* a, int nrAngajati) {
	printf("\n---Lista Angajati---\n");
	for (int i = 0; i < nrAngajati; i++) {
		afisareAngajat(a[i]);
	}
}

void adaugaAngajatInVector(Angajat** angajati, int* nrAngajati, Angajat angajatNou) {
	Angajat* aux = (Angajat*)malloc(sizeof(Angajat) *( (*nrAngajati)+1));
	for (int i = 0; i < (*nrAngajati); i++) {
		aux[i] = (*angajati)[i];
	}
	aux[(*nrAngajati)] = angajatNou;
	if (*angajati != NULL) {
		free(*angajati);
	}
	*angajati=aux;
	(*nrAngajati)++;
}

Angajat citireDinFisier(FILE* file) {
	Angajat a;
	char buffer[200];
	char sep[] = ",\n";

	fgets(buffer, 200, file);

	a.id = atoi(strtok(buffer, sep));
	char* aux = strtok(NULL, sep);
	a.nume= (char*)malloc(sizeof(char)*(strlen(aux)+1));
	strcpy_s(a.nume, strlen(aux) + 1, aux);

	aux= strtok(NULL, sep);
	a.departament=(char*)malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy_s(a.departament, strlen(aux) + 1, aux);

	a.salariu = atof(strtok(NULL, sep));
	a.gen = strtok(NULL, sep)[0];
	
	return a;
}

Angajat* citireVectorDinFisier(const char* numeFisier,int* nrAngajati) {
	FILE* file = fopen(numeFisier,"r");
	Angajat* vector = NULL;
	*nrAngajati = 0;

	if (file != NULL) {
		while (!feof(file)) {
			Angajat angajatNou = citireDinFisier(file);
			adaugaAngajatInVector(&vector, nrAngajati, angajatNou);
		}
		fclose(file);
	}
	else {
		printf("Fisierul %s nu a fost gasit\n", numeFisier);
	}
	return vector;
}

void dezalocareVectorAngajati(Angajat** angajati, int* nrAngajati) {
	if (*angajati != NULL) {
		for (int i = 0; i < (*nrAngajati); i++) {
			if ((*angajati)[i].nume != NULL) {
				free((*angajati)[i].nume);
			}
			if ((*angajati)[i].departament != NULL) {
				free((*angajati)[i].departament);
			}
			
		}
		free(*angajati);
	}
	*nrAngajati = 0;
	*angajati = NULL;
}

int main() {
	int nrAngajati = 3;
	Angajat* angajati = citireVectorDinFisier("angajati.txt", &nrAngajati);
	afisareVectorAngajat(angajati, nrAngajati);

	dezalocareVectorAngajati(&angajati, &nrAngajati);
	printf("\nDupa dezalocare\n");
	afisareVectorAngajat(angajati, nrAngajati);
	return 0;
}