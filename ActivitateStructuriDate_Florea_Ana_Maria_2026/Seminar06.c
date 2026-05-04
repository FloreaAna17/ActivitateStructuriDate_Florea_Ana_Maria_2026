#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

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
	strcpy(m1.model, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy(m1.numeSofer, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d | Nr usi: %d | Pret: %.2f | Model: %s | Sofer: %s | Serie: %c\n",
		masina.id, masina.nrUsi, masina.pret, masina.model, masina.numeSofer, masina.serie);
}

typedef struct Nod Nod;
struct Nod {
	Masina masina;
	struct Nod* next;
};

void pushStack(Nod** cap, Masina masina) {
	Nod* first = (Nod*)malloc(sizeof(Nod));
	first->masina = masina; // Shallow copy
	first->next = (*cap);
	(*cap) = first;
}

Masina popStack(Nod** cap) {
	if ((*cap) == NULL) {
		Masina rezultat;
		rezultat.id = -1;
		return rezultat;
	}
	Masina rezultat = (*cap)->masina;
	Nod* temp = (*cap);
	*cap = (*cap)->next; // Mutam capul mai jos
	free(temp);          // Eliberam vechiul varf
	return rezultat;
}

char isEmptyStack(Nod* cap) {
	return cap == NULL;
}

Nod* citireStackMasiniDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	if (!file) {
		return NULL;
	}
	Nod* cap = NULL;
	while (!feof(file)) {
		Masina masina = citireMasinaDinFisier(file);
		pushStack(&cap, masina);
	}
	fclose(file);
	return cap;
}

void dezalocareStivaDeMasini(Nod** stiva) {
	while (!isEmptyStack(*stiva)) {
		Masina extrasa = popStack(stiva);
		if (extrasa.model) free(extrasa.model);
		if (extrasa.numeSofer) free(extrasa.numeSofer);
	}
}

typedef struct NodDublu NodDublu;
struct NodDublu {
	Masina info;
	NodDublu* next;
	NodDublu* prev;
};

typedef struct ListaDubluInlantuita ListaD;
struct ListaDubluInlantuita {
	NodDublu* first;
	NodDublu* last;
};

void enqueue(ListaD* coada, Masina masina) {
	NodDublu* newNod = malloc(sizeof(NodDublu));
	newNod->info = masina;
	newNod->next = NULL;
	newNod->prev = coada->last;

	if (coada->last) {
		coada->last->next = newNod;
	}
	else {
		coada->first = newNod;
	}
	coada->last = newNod;
}

Masina dequeue(ListaD* coada) {
	Masina rezultat;
	rezultat.id = -1;
	if (coada->first) {
		rezultat = coada->first->info; // Shallow copy
		NodDublu* temp = coada->first;

		coada->first = temp->next;

		if (coada->first != NULL) {
			coada->first->prev = NULL;
		}
		else {
			coada->last = NULL;
		}

		free(temp);
	}
	return rezultat;
}

ListaD citireCoadaDeMasiniDinFisier(const char* numeFisier) {
	ListaD coada;
	coada.first = coada.last = NULL;
	FILE* f = fopen(numeFisier, "r");
	if (f) {
		while (!feof(f)) {
			enqueue(&coada, citireMasinaDinFisier(f));
		}
		fclose(f);
	}
	return coada;
}

void dezalocareCoadaDeMasini(ListaD* coada) {
	while (coada->first != NULL) {
		Masina extrasa = dequeue(coada);
		if (extrasa.model) free(extrasa.model);
		if (extrasa.numeSofer) free(extrasa.numeSofer);
	}
}

int main() {
	
	printf("=== TEST STIVA ===\n");
	Nod* stiva = citireStackMasiniDinFisier("masini.txt");

	
	Masina masinaDinVarf = popStack(&stiva);
	if (masinaDinVarf.id != -1) {
		printf("S-a extras din varful stivei (ultima citita):\n");
		afisareMasina(masinaDinVarf);
		free(masinaDinVarf.model);
		free(masinaDinVarf.numeSofer);
	}
	dezalocareStivaDeMasini(&stiva);
	printf("Stiva dezalocata.\n\n");


	
	printf("=== TEST COADA ===\n");
	ListaD coada = citireCoadaDeMasiniDinFisier("masini.txt");

	// Scoatem primul element asezat la rand
	Masina primaMasinaAsezata = dequeue(&coada);
	if (primaMasinaAsezata.id != -1) {
		printf("S-a extras de la inceputul cozii (prima citita):\n");
		afisareMasina(primaMasinaAsezata);
		free(primaMasinaAsezata.model);
		free(primaMasinaAsezata.numeSofer);
	}
	dezalocareCoadaDeMasini(&coada);
	printf("Coada dezalocata.\n");

	return 0;
}