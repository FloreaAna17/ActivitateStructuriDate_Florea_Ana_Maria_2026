//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Numar usi: %d\n", masina.nrUsi);
//	printf("Pret: %2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Seria: %c\n\n", masina.serie);
//}
//
//void afisareVectorMasini(Masina* masini, int nrMasini) {
//	for (int i = 0; i < nrMasini; i++) {
//		afisareMasina(masini[i]);
//	}
//}
//
//void adaugaMasinaInVector(Masina** masini, int * nrMasini, Masina masinaNoua) {
//	Masina* temp = (Masina*)malloc(sizeof(Masina) *((*nrMasini) + 1));
//	for (int i = 0; i < *nrMasini; i++) {
//		temp[i] = (*masini)[i];//trebuie sa deferentiem pentru ca este pointer la pointer
//	}
//	temp[*nrMasini]= masinaNoua;
//	//in heap noi ne ocupam de gestionarea memoriei
//	free(*masini);
//	(*masini) = temp;
//	(*nrMasini)++;
//}
//
//Masina citireMasinaFisier(FILE* file) {
//	Masina m;
//	char buffer[50];
//	fgets(buffer,50,file);
//	char var[3] = ",\n";
//
//	m.id = atoi(strtok(buffer, var));
//	m.nrUsi= atoi(strtok(NULL, var));//punem NULL pentru ca trebuie sa reia de unde si a lasat flag ul
//	m.pret=atof(strtok(NULL, var));
//	char* aux=strtok(NULL,var);
//	m.model = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
//	strcpy(m.model, aux);
//	aux=strtok(NULL, var);
//	m.numeSofer= (char*)malloc(sizeof(char) * (strlen(aux) + 1));
//	strcpy(m.numeSofer, aux);
//	m.serie= strtok(NULL, var)[0];
//
//	return m;
//}
//
//Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
//	FILE* file;
//	file=fopen(numeFisier,"r");//r de la read - vrem sa citim din acest fisier
//	Masina* masini = NULL;
//	*nrMasiniCitite = 0;
//	while (!feof(file)) {
//		adaugaMasinaInVector(&masini, nrMasiniCitite, citireMasinaFisier(file)); //ii dam adresa ca isi ia el pointer e deja *
//		//e incrementat deja in functie
//	}
//	//EOF = e un flag, care atunci cand ajungem la sfarsitul fisierului si folosim feof ca sa verificam
//	fclose(file);
//	return masini;
//
//}
//
//void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
//
//	for (int i = 0; i < (*nrMasini); i++) {
//		free((*vector)[i].model);
//		free((*vector)[i].numeSofer);
//	}
//
//	free(*vector);
//	*vector = NULL;
//	(*nrMasini) = 0;
//	//este dezalocat intreg vectorul de masini
//	// parcurgem vectorul de masini si la fiecare dezalocam model si numesofer
//}
//
//int main() {
//
//	int nrMasini = 10;
//	Masina* masini = NULL;
//	masini = citireVectorMasiniFisier("Masini.txt", &nrMasini);
//	afisareVectorMasini(masini, nrMasini);
//
//	return 0;
//}
////-> deferentiere si deplasare 
////(*vector) deferentiere si accesare