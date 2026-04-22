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
};
typedef struct Nod Nod;

Angajat citireAngajatDinFisier(FILE* file) {
	Angajat angajat;
	char sep[] = ",\n";
	char buffer[100];

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

void afisareListaAngajati(Nod* cap) {
	while(cap) {
		afisareAngajat(cap->info);
		cap = cap->next;
	}
}

void adaugaLaSfarsitInLista(Nod** cap, Angajat angajat) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = angajat;
	nou->next = NULL;

	if (*cap) {
		Nod* p = *cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}
	else {
		*cap = nou;
	}

}

void adaugaLaInceputInLista(Nod** cap, Angajat angajat) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = angajat;
	nou->next = *cap;
	*cap = nou;
}

Nod* citireAngajatiDinFisier(const char* numeFisier) {
	Nod* cap = NULL;
	FILE* file = fopen(numeFisier, "r");
	if (file) {
		while (!feof(file)) {
			adaugaLaInceputInLista(&cap, citireAngajatDinFisier(file));
		}
	}
	fclose(file);
	return cap;
}

void dezalocareListaAngajati(Nod** cap) {
	while (*cap) {
		Nod* p = *cap;
		*cap = p->next;
		if (p->info.nume != NULL) {
			free(p->info.nume);
		}
		if (p->info.departament != NULL) {
			free(p->info.departament);
		}
		free(p);
	}
	
}
int main() {
	Nod* cap = citireAngajatiDinFisier("angajati.txt");
	afisareListaAngajati(cap);
	dezalocareListaAngajati(&cap);
	afisareListaAngajati(cap);
	return 0;
}