#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//daca avem ca gradul de echilibru -2/2 => dezechilibru
//verificam daca gradul este pozitiv sau negativ=> ne dam seama unde facem rotirea
//daca e cu minus facem dubla rotire


struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;
struct NodArbore {
	Masina info;
	NodArbore* stanga;
	NodArbore* dreapta;
};
typedef struct NodArbore NodArbore;
Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

int calculeazaInaltimeArbore(NodArbore* radacina) {
	if(radacina) {
		int dr = calculeazaInaltimeArbore(radacina->dreapta);
		int st = calculeazaInaltimeArbore(radacina->stanga);
		return 1 + max(dr, st);
	}
	else {
		return 0;
	}
	
}

NodArbore* rotireStanga(NodArbore** radacina) {
	NodArbore* aux = (*radacina)->dreapta;
	(*radacina)->dreapta = aux->stanga;
	aux->stanga = (*radacina);
	(*radacina) = aux;
}

NodArbore* rotireDreapta(NodArbore** radacina) {
	NodArbore* aux = (*radacina)->stanga;
	(*radacina)->stanga = aux->dreapta;
	aux->dreapta = (*radacina);
	(*radacina) = aux;
}

void adaugaMasinaInArboreEchilibrat(NodArbore** radacina, Masina masinaNoua) {
	if ((*radacina) != NULL) {
		if (masinaNoua.id > (*radacina)->info.id) {
			adaugaMasinaInArboreEchilibrat(&(*radacina)->dreapta, masinaNoua);
		}
		else {
			adaugaMasinaInArboreEchilibrat(&(*radacina)->stanga, masinaNoua);
		}
		int factorEchilibru = verificareEchilibru(*radacina);
		if (factorEchilibru == -2) {
			//dezechilibru dreapta
			if (verificareEchilibru((*radacina)->dreapta == -1)) {
				rotireStanga(&(*radacina));
			}
			else {
				rotireDreapta(&(*radacina)->dreapta);
				rotireStanga(&(*radacina));
			}
		}
		if (factorEchilibru == 2) {
			//dezechilibru stanga
			if (verificareEchilibru((*radacina)->stanga) == -1) {
				rotireStanga(&(*radacina)->stanga);
			}
			rotireDreapta(&(*radacina));
		}
	}
	else {
		NodArbore* nou = (NodArbore*)malloc(sizeof(NodArbore));
		nou->stanga = NULL;
		nou->dreapta = NULL;
		nou->info = masinaNoua;
		(*radacina) = nou;
	}
}
int verificareEchilibru(NodArbore* radacina) {
	return calculeazaInaltimeArbore(radacina->stanga) - calculeazaInaltimeArbore(radacina->dreapta);
}
void* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	NodArbore* radacina = NULL;
	if (file) {
		while (!feof(file)) {
			adaugaMasinaInArboreEchilibrat(&radacina, citireMasinaDinFisier(file));
		}
	}
	fcloe(file);
	return radacina;
}

void afisareMasiniDinArbore(NodArbore* radacina) {
	if (radacina) {
		afisareMasina(radacina->info);
		afisareMasiniDinArbore(radacina->stanga);
		afisareMasiniDinArbore(radacina->dreapta);
	}
}

void dezalocareArboreDeMasini(/*arbore de masini*/) {
	//sunt dezalocate toate masinile si arborele de elemente
}

//Preluati urmatoarele functii din laboratorul precedent.
//Acestea ar trebuie sa functioneze pe noul arbore echilibrat.

Masina getMasinaByID(/*arborele de masini*/int id);

int determinaNumarNoduri(/*arborele de masini*/);

float calculeazaPretTotal(/*arbore de masini*/);

float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer);

int main() {
	NodArbore* radacina = citireArboreDeMasiniDinFisier("masini.txt");
	afisareMasiniDinArbore(radacina);

	return 0;
}