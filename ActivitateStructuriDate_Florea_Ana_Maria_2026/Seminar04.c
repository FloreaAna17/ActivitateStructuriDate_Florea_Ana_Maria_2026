//datele din lista vor fi de acelasi tip
//fiecare element contine adresa urmatorului element
//structura de date omogena,liniara- nu ocupa o zona de memorie contigua

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//ne folosim de fisierul masini.txt

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

struct Nod {
	Masina info;
	struct Nod* next;
};

typedef struct Nod Nod;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret= atof(strtok(NULL, sep));
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

void afisareListaMasini(Nod*cap) {
	while (cap != NULL) {
		afisareMasina(cap->info);
		cap = cap->next;
	}
	
}

void adaugaMasinaInLista(Nod**cap, Masina masinaNoua) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = masinaNoua;
	nodNou->next = NULL;
	if ((*cap)==NULL) {
		(*cap) = nodNou;
	}
	else {
		Nod* aux = *cap;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nodNou;
	}
}

void adaugaLaInceputInLista(Nod**cap,Masina masinaNoua) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = masinaNoua;
	nodNou->next = *cap;
	*cap = nodNou;
}

void* citireListaMasiniDinFisier(const char* numeFisier) {//putem pune Nod* citire..

	FILE* file = fopen(numeFisier, "r");
	if (file) {
		Nod* cap = NULL;
		while (!feof(file)) {
			adaugaMasinaInLista(&cap,citireMasinaDinFisier(file));
		}
		fclose(file);
		return cap;
	}
	return NULL;
	//este functie de tip pointer la void - pointer la orice (stramosul lui template-poo)
}

void dezalocareListaMasini(Nod**cap) {
	//sunt dezalocate toate masinile si lista de elemente
	while (*cap) {
		Nod* p = *cap;
		(*cap) = p->next;
		if (p->info.numeSofer) {
			free(p->info.numeSofer);
		}
		if (p->info.model) {
			free(p->info.model);
		}
		free(p);
	}
}

float calculeazaPretMediu(Nod*cap) {
	float suma = 0;
	int contor = 0;
	while (cap) {
		suma += cap->info.pret;
		contor++;
		cap = cap->next;
	}
	if (contor > 0) {
		return suma / contor;
	}
	
	return 0;
}

void stergeMasiniDinSeria(Nod** cap, char serieCautata) {
	while ((*cap) && (*cap)->info.serie == serieCautata) {

		Nod* temp = *cap;
		(*cap) = temp->next;

		if (temp->info.numeSofer) {
			free(temp->info.numeSofer);
		}
		if (temp->info.model) {
			free(temp->info.model);
		}
		free(temp);
	}
	Nod* p = *cap;
	while (p) {

		while ((*p).next && (*p).next->info.serie != serieCautata) {
			p = p->next;
		}
		Nod* temp = p->next;
		if (p->next) {
			p->next = temp->next;
			if (p->info.model) {
				free(temp->info.model);
			}
			if (p->info.numeSofer) {
				free(temp->info.numeSofer);
			}
			free(temp);
		}
		else {
			p = p->next;
		}
	}
}

float calculeazaPretulMasinilorUnuiSofer(Nod* cap, const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	float pretT = 0;
	while (cap != NULL) {
		if (strcmp(cap->info.numeSofer, numeSofer) == 0) {
			pretT = pretT + cap->info.pret;
		}
		cap = cap->next;
	}
	return pretT;
}

int main() {

	Nod* cap = NULL;
	cap = citireListaMasiniDinFisier("masini.txt");
	afisareListaMasini(cap);

	//dezalocareListaMasini(&cap);
	afisareListaMasini(cap);
	printf("Lista dupa dezalocare!\n");

	float valoare = 0;
	valoare=calculeazaPretMediu(cap);
	printf("Pret mediu: %.2f", valoare);

	printf("Stergere serie:\n");
	stergeMasiniDinSeria(&cap,'A');
	printf("Dupa stergerea seriei:\n");
	afisareListaMasini(cap);

	float total;
	total = calculeazaPretulMasinilorUnuiSofer(cap, "Ionescu");
	printf("Pretul total al masinilor conduse de %s este: %2.f\n", "Ionescu", total);

	return 0;
}