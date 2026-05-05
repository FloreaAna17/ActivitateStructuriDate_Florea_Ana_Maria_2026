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

}

int main() {

	return 0;
}