#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

struct Angajat {
	int id; 
	char* nume;
	char* departament;
	float salariu;
};

//initializare
struct Angajat initializare(int id, const char* nume, const char* departament, float salariu) {
	struct Angajat a;
	a.id = id;
	a.salariu = salariu;

	a.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy_s(a.nume, strlen(nume) + 1, nume);
	a.departament = (char*)malloc(sizeof(char) * (strlen(departament) + 1));
	strcpy_s(a.departament, strlen(departament) + 1, departament);

	return a;
}

//afisare
void afisare(struct Angajat a) {
	printf("%d. Angajatul %s din departamentul %s are salariul %.2f", a.id, a.nume, a.departament, a.salariu);
	printf("\n--------------------------------\n");
}

//functie de transferare in alt departament

//dezalocare
void dezalocare(struct Angajat* a) {
	
	if (a->nume != NULL) {
		free(a->nume);
		a->nume = NULL;
	}
	if (a->departament != NULL) {
		free(a->departament);
		a->departament = NULL;
	}
}

int main() {
	struct Angajat a;
	a = initializare(1, "Ana", "IT", 3200.5);
	afisare(a);

	dezalocare(&a);
	afisare(a);
	return 0;
}