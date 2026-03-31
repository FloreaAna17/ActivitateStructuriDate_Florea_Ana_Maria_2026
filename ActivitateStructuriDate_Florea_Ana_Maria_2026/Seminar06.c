#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

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

typedef struct Nod Nod;
struct Nod {
	Masina masina;
	struct Nod* next;
};


//STACK
//Alegeti prin ce veti reprezenta stiva si creati structura necesara acestei stive
//putem reprezenta o stiva prin LSI, LDI sau vector - de incercat si cu LDI/vector

void pushStack(Nod** cap, Masina masina) {
	Nod* first = (Nod*)malloc(sizeof(Nod));
	first->masina = masina;
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
	Nod* temp = (*cap)->next;//shallow copy
	free(*cap);
	*cap = temp;
	return rezultat;

}

char isEmptyStack(Nod* cap) {//punem char pt ca ocupa un singur octet - nu avem bool in C
	return cap == NULL;
}

void* citireStackMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul

	FILE *file = fopen(numeFisier, "r");
	if (!file) {
		return NULL;
	}
	Nod* cap = NULL;
	while(!feof(file)) {
		Masina masina = citireMasinaDinFisier(file);
		pushStack(&cap, masina);
	}
	fclose(file);
	return cap;
}

void dezalocareStivaDeMasini(/*stiva*/) {
	//sunt dezalocate toate masinile si stiva de elemente
}

int size(/*stiva*/) {
	//returneaza numarul de elemente din stiva
}

//QUEUE
//Alegeti prin ce veti reprezenta coada si creati structura necesara acestei cozi
//putem reprezenta o coada prin LSI, LDI sau vector
void enqueue(/*coada*/ Masina masina) {
	//adauga o masina in coada
}

Masina dequeue(/*coada*/) {
	//extrage o masina din coada
}

void* citireCoadaDeMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
}

void dezalocareCoadaDeMasini(/*coada*/) {
	//sunt dezalocate toate masinile si coada de elemente
}


//metode de procesare
Masina getMasinaByID(Nod** stiva,int id) {
	Masina rezultat;
	if ((*stiva) == NULL) {
		rezultat.id = -1;
		return rezultat;
	}
	Nod* stivaNoua = NULL;
	while ((*stiva)) {
		Masina masinaNoua = popStack(stiva);
		if (masinaNoua.id == id) {
			rezultat = masinaNoua;
			break;
		}
		pushStack(&stivaNoua, masinaNoua);
	}
	while (stivaNoua) {
		pushStack(stiva, popStack(&stivaNoua));
	 }
	return rezultat;
};

float calculeazaPretTotal(/*stiva sau coada de masini*/);

int main() {
	Nod* stiva = citireStackMasiniDinFisier("masini.txt");
	afisareMasina(popStack(&stiva));
	afisareMasina(popStack(&stiva));

	afisareMasina(getMasinaByID(&stiva,4));
	return 0;
}