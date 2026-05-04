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

struct Nod {
	struct Nod* stanga;
	struct Nod* dreapta;
	Masina info;
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


void adaugaMasinaInArbore(Nod** radacina, Masina masinaNoua) {
	//adauga o noua masina pe care o primim ca parametru in arbore,
	//astfel incat sa respecte princiippile de arbore binar de cautare
	//dupa o anumita cheie pe care o decideti - poate fi ID
	if (*radacina) {
		if ((*radacina)->info.id < masinaNoua.id) {
			adaugaMasinaInArbore(&(*radacina)->dreapta, masinaNoua);
		}
		if ((*radacina)->info.id > masinaNoua.id) {
			adaugaMasinaInArbore(&(*radacina)->stanga, masinaNoua);
		}
	}
	else {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = masinaNoua;
		nou->stanga = NULL;
		nou->dreapta = NULL;
		*radacina = nou;
	}
}

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	Nod* radacina = NULL;
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		adaugaMasinaInArbore(&radacina, citireMasinaDinFisier(f));
	}
	fclose(f);
	return radacina;
}

void afisareMasiniDinArbore(Nod* radacina) {
	//afiseaza toate elemente de tip masina din arborele creat
	//prin apelarea functiei afisareMasina()
	//parcurgerea arborelui poate fi realizata in TREI moduri
	//folositi toate cele TREI moduri de parcurgere
	if (radacina) {
		afisareMasiniDinArbore(radacina->stanga);
		afisareMasina(radacina->info);
		afisareMasiniDinArbore(radacina->dreapta);
	}
}

void afisareMasiniDinArborePreordine(Nod* radacina) {
	//afiseaza toate elemente de tip masina din arborele creat
	//prin apelarea functiei afisareMasina()
	//parcurgerea arborelui poate fi realizata in TREI moduri
	//folositi toate cele TREI moduri de parcurgere
	if (radacina) {
		afisareMasina(radacina->info);
		afisareMasiniDinArborePreordine(radacina->stanga);
		afisareMasiniDinArborePreordine(radacina->dreapta);
	}
}

void dezalocareArboreDeMasini(Nod** radacina) {
	//sunt dezalocate toate masinile si arborele de elemente
	if (*radacina) {
		dezalocareArboreDeMasini(&(*radacina)->stanga);
		dezalocareArboreDeMasini(&(*radacina)->dreapta);
		free((*radacina)->info.numeSofer);
		free((*radacina)->info.model);
		free(*radacina);
		*radacina = NULL;
	}
}

Masina getMasinaByID(Nod* radacina, int idCautat) {

	if (radacina) {
		if (radacina->info.id == idCautat) {
			Masina m = radacina->info;
			m.model = (char*)malloc(strlen(radacina->info.model) + 1);
			strcpy(m.model, radacina->info.model);

			m.numeSofer = (char*)malloc(strlen(radacina->info.numeSofer) + 1);
			strcpy(m.numeSofer, radacina->info.numeSofer);
			return m;
		}
		if (radacina->info.id < idCautat) {
			return getMasinaByID(radacina->dreapta, idCautat);
		}
		if (radacina->info.id > idCautat) {
			return getMasinaByID(radacina->stanga, idCautat);
		}
	}
	else {
		Masina m;
		m.id = -1;
		return m;

	}


}

int determinaNumarNoduri(Nod* radacina) {
	//calculeaza numarul total de noduri din arborele binar de cautare
	if (radacina) {
		return determinaNumarNoduri(radacina->stanga) + determinaNumarNoduri(radacina->dreapta) + 1;
	}
	return 0;
}

int calculeazaInaltimeArbore(Nod* radacina) {
	//calculeaza inaltimea arborelui care este data de 
	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza
	if (radacina) {
		int inaltStg = calculeazaInaltimeArbore(radacina->stanga);
		int inaltDrp = calculeazaInaltimeArbore(radacina->dreapta);
		return inaltStg > inaltDrp ? inaltStg + 1 : inaltDrp + 1;

	}
	return 0;
}

float calculeazaPretTotal(Nod* radacina) {
	//calculeaza pretul tuturor masinilor din arbore.

	if (radacina) {
		return calculeazaPretTotal(radacina->stanga) + calculeazaPretTotal(radacina->dreapta) + radacina->info.pret;
	}
	return 0;
}

float calculeazaPretulMasinilorUnuiSofer(Nod* radacina, const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.

	if (radacina) {
		float suma = calculeazaPretulMasinilorUnuiSofer(radacina->stanga, numeSofer) + calculeazaPretulMasinilorUnuiSofer(radacina->dreapta, numeSofer);
		if (strcmp(radacina->info.numeSofer, numeSofer) == 0) {
			return suma + radacina->info.pret;
		}
		else {
			return suma;
		}
	}
	else {
		return 0;
	}
	return 0;
}

int main() {
	Nod* radacina = citireArboreDeMasiniDinFisier("masini_arbore.txt");
	afisareMasiniDinArbore(radacina);
	afisareMasina(getMasinaByID(radacina, 5));
	printf(" Numar noduri: %d\n", determinaNumarNoduri(radacina));
	printf(" Inaltime arbore: %d\n", calculeazaInaltimeArbore(radacina));
	printf(" Pret total: %5.2f\n", calculeazaPretTotal(radacina));
	printf(" Pret total masini in functie de numele soferului: %5.2f\n", calculeazaPretulMasinilorUnuiSofer(radacina, "Ionescu"));

	dezalocareArboreDeMasini(&radacina);
	printf("Dupa dezalocare\n");
	afisareMasiniDinArbore(radacina);

	return 0;
}