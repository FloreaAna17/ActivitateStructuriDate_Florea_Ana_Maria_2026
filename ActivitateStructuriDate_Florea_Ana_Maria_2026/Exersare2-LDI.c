#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

struct StructuraAngajat {
		int id;
		char* nume;
		char* departament;
		float salariu;
		char gen;
	};
typedef struct StructuraAngajat Angajat;
struct Nod {
	Angajat info;
	struct Nod* next;
	struct Nod* prev;
};
typedef struct Nod Nod;
struct ListaDubla {
	Nod* first;
	Nod* last;
	int nrNoduri;
};
typedef struct ListaDubla ListaDubla;

Angajat citireAngajatDinFisier(FILE* file) {
	Angajat angajat;
	char buffer[100];
	char sep[] = ",\n";

	fgets(buffer, 100, file);
	angajat.id = atoi(strtok(buffer, sep));
	
		char* aux = strtok(NULL, sep);
		angajat.nume = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
		strcpy_s(angajat.nume, strlen(aux) + 1, aux);
	
		aux = strtok(NULL, sep);
		angajat.departament = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
		strcpy_s(angajat.departament, strlen(aux) + 1, aux);
	
		angajat.salariu = atof(strtok(NULL, sep));
		angajat.gen = strtok(NULL, sep)[0];
	
		return angajat;

}
void afisareAngajat(Angajat angajat) {
	printf("Id: %d\n", angajat.id);
	printf("Nume: %s\n", angajat.nume);
	printf("Departament: %s\n", angajat.departament);
	printf("Salariu: %.2f\n", angajat.salariu);
	printf("Gen: %c\n", angajat.gen);
 }
void afisareListaAngajatiDeLaInceput(ListaDubla lista) {
	Nod* p = lista.first;
	while (p) {
		afisareAngajat(p->info);
		p = p->next;
	}
 }
void afisareListaAngajatiDeLaSfarsit(ListaDubla lista) {
	Nod* p = lista.last;
	while (p) {
		afisareAngajat(p->info);
		p = p->prev;
	}
}
void adaugaAngajatLaInceput(ListaDubla* lista, Angajat a) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = a;
	nou->next = lista->first;
	nou->prev = NULL;
	if (lista->first != NULL) {
		lista->first->prev = nou;
	}
	else {
		lista->last = nou;
	}
	lista->first = nou;
	lista->nrNoduri++;
}
void adaugaAngajatLaSfarsit(ListaDubla* lista, Angajat a) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = a;
	nou->next = NULL;
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
ListaDubla citireListaAngajatiDinFisier(const char* numeFisier) {
	ListaDubla lista;
	lista.first = NULL;
	lista.last = NULL;
	lista.nrNoduri = 0;
	FILE* file = fopen(numeFisier, "r");
	if (file) {
		while (!(feof(file))) {
			adaugaAngajatLaSfarsit(&lista, citireAngajatDinFisier(file));
		}
	}
	fclose(file);
	return lista;
}
void dezalocare(ListaDubla* lista) {
	Nod* p = lista->first;
	while (p) {
		Nod* aux = p;
		p = p->next;
		if (aux->info.nume != NULL) {
			free(aux->info.nume);
		}
		if (aux->info.departament != NULL) {
			free(aux->info.departament);
		}
		free(aux);
	}
	lista->first = NULL;
	lista->last = NULL;
	lista->nrNoduri = 0;
}
int main() {
	ListaDubla lista = citireListaAngajatiDinFisier("angajati.txt");
	afisareListaAngajatiDeLaSfarsit(lista);
	afisareListaAngajatiDeLaSfarsit(lista);
	dezalocare(&lista);
	afisareListaAngajatiDeLaInceput(lista);
	return 0;
}