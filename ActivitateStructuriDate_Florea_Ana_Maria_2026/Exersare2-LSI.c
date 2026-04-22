#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<stdio.h>

struct StructuraProdus {
	int id;
	char* nume; 
	char* categorie;
	float pret;
};

typedef struct StructuraProdus Produs;

struct Nod {
	Produs info;
	struct Nod* next;
};
typedef struct Nod Nod;

Produs citireProdusDinFisier(FILE* file) {
	Produs p;
	char sep[] = ",\n";
	char buffer[100];

	fgets(buffer, 100, file);

	p.id = atoi(strtok(buffer, sep));

	char* aux = strtok(NULL, sep);
	p.nume = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy_s(p.nume, strlen(aux) + 1, aux);

	aux= strtok(NULL, sep);
	p.categorie= (char*)malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy_s(p.categorie, strlen(aux) + 1, aux);

	p.pret = atof(strtok(NULL, sep));

	return p;
}

void afisareProdus(Produs p) {
	printf("Id: %d\n", p.id);
	printf("Nume : %s\n", p.nume);
	printf("Categorie %s\n",p.categorie);
	printf("Pret: %.2f\n", p.pret);
	
}

void afisareListaProduse(Nod* cap) {
	while (cap != NULL) {
		printf("%d. Produsul %s din categoria %s are pretul %.2f\n", cap->info.id, cap->info.nume, cap->info.categorie, cap->info.pret);
		cap = cap->next;
	}
}

void adaugaLaSfarsitInLista(Nod** cap,Produs produsNou) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = produsNou;
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
void adaugareLaInceputInLista(Nod** cap, Produs produsNou) {
	Nod* nou = NULL;
	nou->info = produsNou;
	nou->next = *cap;
	*cap = nou;
}

Nod* citireProduseDinFisier(const char* numeFisier) {
	Nod* cap = NULL;
	FILE* file = fopen(numeFisier, "r");
	if (file) {
		while (!feof(file)) {
			adaugaLaSfarsitInLista(&cap, citireProdusDinFisier(file));
		}
	}
	fclose(file);
	return cap;
}

void dezalocareListaProduse(Nod** cap) {
	while (*cap) {
		Nod* p = *cap;
		(*cap) = p->next;
		if (p->info.nume != NULL) {
			free(p->info.nume);
		}
		if (p->info.categorie != NULL) {
			free(p->info.categorie);
		}
		free(p);
	}
}
int main() {
	Nod* cap = citireProduseDinFisier("produse.txt");
	afisareListaProduse(cap);
	dezalocareListaProduse(&cap);
	afisareListaProduse(cap);


	return 0;
}