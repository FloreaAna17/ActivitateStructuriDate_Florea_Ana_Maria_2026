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

//daca punem typedef struct Nod Nod; inainte de struct Nod putem pune in interior doar Nod* next ....

struct Nod {
	Masina info;
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

void afisareListaMasini(ListaDubla lista) {
	Nod* p = lista.first;
	while (p) {
		afisareMasina(p->info);
		p = p->next;
	}
	printf("Lista contine %d noduri:\n", lista.nrNoduri);
}

void afisareInversaListaMasini(ListaDubla lista) {
	Nod* p = lista.last;
	while (p) {
		afisareMasina(p->info);
		p = p->prev;
	}

}

void adaugaMasinaInLista(ListaDubla* lista, Masina masinaNoua) {// inserare la sfarsit
	Nod* p = (Nod*)malloc(sizeof(Nod));
	p->prev = lista->last;
	p->next = NULL;
	p->info = masinaNoua;
	if (lista->last) {
		lista->last->next = p;
	}
	else {
		lista->first = p;
	}
	lista->last = p;
	lista->nrNoduri++;
	
}

void adaugaLaInceputInLista(ListaDubla* lista, Masina masinaNoua) {
	Nod* p= (Nod*)malloc(sizeof(Nod));
	p->prev = NULL;
	p->next = lista->first;
	p->info = masinaNoua;
	if (lista->first) {
		lista->first->prev = p;
	}
	else {
		lista->last = p;
	}
	lista->first = p;
	lista->nrNoduri++;
}

ListaDubla citireLDMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	ListaDubla lista;
	lista.last= NULL;
	lista.first = NULL;
	lista.nrNoduri = 0;
	if (!f) {
		return lista;
	}
	while (!feof(f)) {
		adaugaMasinaInLista(&lista, citireMasinaDinFisier(f));
	}
	fclose(f);
	return lista;
}

void dezalocareLDMasini(ListaDubla* lista) {
	Nod* nod = lista->first;
	while (nod) {
		Nod* aux = nod; 
		nod = nod->next;
		if (aux->info.model) {
			free(aux->info.model);
		}
		if (aux->info.numeSofer) {
			free(aux->info.numeSofer);
		}
		free(aux);
		lista->nrNoduri--;
	}
	lista->first = NULL;
	lista->last = NULL;
}

float calculeazaPretMediu(ListaDubla* lista) {
	float pretTotal = 0;
	if (lista->first == NULL) {
		return 0;
	}
	else {
		/*Nod* p = lista->first;
		while (p) {
			pretTotal = p->info.serie;
			p = p->next;*/

		for (Nod* p = lista->first; p != NULL; p = p->next) {
			pretTotal += p->info.pret;//parcurgere lista cu for
		}
	}
	return pretTotal / lista->nrNoduri;
}

void stergeMasinaDupaID(ListaDubla* lista, int id) {
	//modificam si numarul de noduri orice ar fi deci transmitem prin adresa *
	//modificam legaturile

	if (lista->first)
	{
		Nod* p;
		for (p = lista->first; p != NULL && p->info.id != id; p = p->next); //facem parcurgerea
		if (!p) return;
		else
		{
			if (p->prev == NULL)
			{
				Nod* aux = p;
				if (p->next)
				{
					p->next->prev = NULL;
				}
				else
				{
					lista->last = NULL;
				}
				lista->first = p->next;
				free(p->info.model);
				free(p->info.numeSofer);
				free(p);
			}
			else
			{
				p->prev->next = p->next;
				if (p->next)
				{
					p->next->prev = p->prev;
				}
				else
				{
					lista->last = p->prev;
				}
				free(p->info.model);
				free(p->info.numeSofer);
				free(p);
			}
			lista->nrNoduri--;
		}
	}

}

char* getNumeSoferMasinaScumpa(ListaDubla lista) {
	if (lista.first == NULL) {
		return NULL;
	}else{
		Nod* max = lista.first;
		Nod* p = lista.first->next;
		while (p) {
			if (p->info.pret > max->info.pret) {
				max = p;
			}
			p = p->next;
		}
		char* nume = (char*)malloc(strlen(max->info.numeSofer) + 1);
		strcpy_s(nume, strlen(max->info.numeSofer) + 1, max->info.numeSofer);
		return nume;
	}

}

int main() {

	ListaDubla lista;
	lista=citireLDMasiniDinFisier("masini.txt");
	afisareListaMasini(lista);

	char* sofer = getNumeSoferMasinaScumpa(lista);
	if (sofer) {
		printf("Nume soferului care are cea mai scumpa masina este: %s\n\n", sofer);
		free(sofer);
	}

	/*afisareInversaListaMasini(lista);

	printf("Inainte de dezalocare\n");
	afisareListaMasini(lista);

	printf("Pretul mediu:%2.f\n", calculeazaPretMediu(&lista));

	dezalocareLDMasini(&lista);
	printf("Dupa dezalocare\n");
	afisareListaMasini(lista);*/

	stergeMasinaDupaID(&lista, 1);
	afisareListaMasini(lista);
	return 0;
}