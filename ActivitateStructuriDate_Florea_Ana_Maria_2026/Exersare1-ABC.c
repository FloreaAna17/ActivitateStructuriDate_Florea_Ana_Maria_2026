#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

struct Laptop {
	int id;
	char* producator;
	char* procesor;
	float pret;
};

typedef struct Laptop Laptop;

struct NodArbore {
	Laptop info;
	struct NodArbore* stanga;
	struct NodArbore* dreapta;
};
typedef struct NodArbore NodArbore;

void afisare(Laptop l) {
	printf("ID: % d | Producator : % -8s | Procesor : % -15s | Pret : % .2f\n", 
		l.id, l.producator, l.procesor, l.pret);
}
Laptop citireLaptop(FILE f) {
	char buffer[200];
	char sep[] = ", \n";
	Laptop l;

	fgets(buffer, 200, sep);
	l.id = atoi(strtok(buffer, sep));

	char* aux = strtok(NULL, sep);
	l.producator = (char*)malloc(strlen(aux) + 1);
	strcpy(l.producator, aux);

	aux = strtok(NULL, sep);
	l.procesor = (char*)malloc(strlen(aux) + 1);
	strcpy(l.procesor, aux);

	l.pret = atof(strtok(NULL, sep));

	return l;
}

void inserareInArbore(NodArbore** radacina, Laptop l) {
	if (*radacina) {
		if (l.id<(*radacina)->info.id) {
			inserareInArbore(&(*radacina)->stanga, l);
		}
		else {
			if (l.id > (*radacina)->info.id) {
				inserareInArbore(&(*radacina)->dreapta, l);
			}
		}
	}
	else {
		NodArbore* nou = (NodArbore*)malloc(sizeof(NodArbore));
		nou->dreapta = NULL;
		nou->stanga = NULL;
		nou->info = l;
		*radacina = nou;
	}
}

NodArbore* citireArboreDinFisier(const char* numeFisier) {
	NodArbore* radacina = NULL;
	FILE* f = fopen(numeFisier, "r");
	if (f != NULL) {
		while (!feof(f)) {
			inserareInArbore(&radacina, citireLaptop(f));
		}
		fclose(f);
	}
	return radacina;
}

int main() {

	return 0;


}