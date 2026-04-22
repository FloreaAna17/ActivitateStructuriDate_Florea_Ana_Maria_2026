#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

struct StructuraLaptop {
	int id;
	char* producator;
	char* procesor;
	float pret;
};

typedef struct StructuraLaptop Laptop;

 struct Nod {
	Laptop info;
	struct Nod* next;
	struct Nod* prev;
};

typedef struct Nod Nod;

struct ListaDubla {
	Nod* last;
	Nod* first;
	int nrNoduri;
};
typedef struct ListaDubla ListaDubla;

Laptop citireLaptopDinFisier(FILE* file) {
	Laptop p;
	char sep[] = ",\n";
	char buffer[100];

	fgets(buffer, 100, file);

	p.id = atoi(strtok(buffer, sep));
	char* aux = strtok(NULL, sep);
	p.producator = (char*)malloc(sizeof(char) *( strlen(aux)+1));
	strcpy_s(p.producator, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	p.procesor = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy_s(p.procesor, strlen(aux) + 1, aux);

	p.pret = atof(strtok(NULL, sep));
	return p;
}
void adaugaLaptopLaSfarsit(ListaDubla* lista, Laptop l) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = l;
	nou->next=NULL;
	nou->prev = lista->last;
	if (lista->last != NULL) {
		lista->last->next = nou;
	}
	else {
		lista->first = nou;
	}
	lista->last = nou;
	lista->nrNoduri++;
}

ListaDubla citireListeDinFisier(const char* numeFisier) {
	ListaDubla lista;
	lista.first = NULL;
	lista.last = NULL;
	lista.nrNoduri = 0;
	FILE* file = fopen(numeFisier, "r");
	if (file) {
		while (!feof(file)) {
			adaugaLaptopLaSfarsit(&lista, citireLaptopDinFisier(file));
		}
		fclose(file);
	}

	return lista;
}

void afisareLaptop(Laptop p) {
	printf("ID: %d | Producator: %s | Procesor: %s | Pret: %.2f\n",
		p.id, p.producator, p.procesor, p.pret);
}
void afisareLista(ListaDubla lista) {
	Nod* p = lista.first;
	while (p) {
		afisareLaptop(p->info);
		p = p->next;
	}
}

void dezalocare(ListaDubla lista) {
	Nod* p = lista.first;
	while (p) {
		Nod* aux = p;
		p = p->next;
		if (aux->info.procesor != NULL) {
			free(aux->info.procesor);
		}
		if (aux->info.producator != NULL) {
			free(aux->info.producator);
		}
		free(aux);
	}
	lista.first = NULL;
	lista.last=NULL;
	lista.nrNoduri = 0;
}
//void afisareLaptop(Laptop laptop) {
//	printf("Id: %d\n", laptop.id);
//	printf("Producator: %s\n", laptop.producator);
//	printf("Procesor: %s\n", laptop.procesor);
//	printf("Pret: %.2f\n", laptop.pret);
//}

int main() {
	ListaDubla lista = citireListeDinFisier("laptopuri.txt");
	afisareLista(lista);
}
