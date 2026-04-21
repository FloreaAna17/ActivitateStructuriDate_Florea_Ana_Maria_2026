//# define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<malloc.h>
//#include<string.h>
//#include<stdlib.h>
//
//struct Produs {
//	int id;
//	char* denumire;
//	float pret;
//	char categorie;
//};
//
////functia de initializare
//struct Produs initializare(int id,const char* denumire,float pret,char categorie) {
//	struct Produs p;
//	p.id = id;
//	p.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
//	strcpy_s(p.denumire,strlen(denumire) + 1, denumire);
//	p.pret = pret;
//	p.categorie = categorie;
//	return p;
//}
//
//void modifica_pret(struct Produs* p,float pretNou) {
//	if (p->pret > 0) {
//		p->pret = pretNou;
//	}
//}
//
////functia de afisare
//void afisare(struct Produs p) {
//	printf("%d. %s are pretul %5.2f din categoria %c\n", p.id, p.denumire, p.pret, p.categorie);
//}
//
////functia de dezalocare
//void dezalocare(struct Produs* p) {
//	if (p->denumire != NULL) {
//		free(p->denumire);
//		p->denumire = NULL;
//	}
//}
//
//int main() {
//	struct Produs p;
//	p = initializare(1, "Laptop", 1200.5, 'A');
//	afisare(p);
//
//	modifica_pret(&p, 100);
//	afisare(p);
//
//	dezalocare(&p);
//	afisare(p);
//	return 0;
//}