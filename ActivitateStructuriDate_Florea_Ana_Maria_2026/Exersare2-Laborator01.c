//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include<stdlib.h>
//#include<malloc.h>
//
//struct Student {
//	int id;
//	char* nume;
//	int* note;
//	int nrNote;
//	float medie;
//};
//
////initializare
//struct Student initializare(int id,const char* nume,const int* note,int nrNote) {
//	struct Student s;
//	s.id = id;
//	s.nrNote = nrNote;
//
//	s.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
//	strcpy_s(s.nume, strlen(nume) + 1, nume);
//
//	s.note = (int*)malloc(sizeof(int) * nrNote);
//	float suma = 0; //calculam suma pentru medie
//	if (s.note) {
//		for (int i = 0; i < nrNote; i++) {
//			s.note[i] = note[i];
//			suma = suma + note[i];
//		}
//	}
//
//	if (nrNote > 0) {
//		s.medie = suma / nrNote;
//	}
//	else {
//		s.medie = 0;
//	}
//	return s;
//}
//
////afisare
//void afisare(struct Student s) {
//	printf("%d. Student: %s, Medie: %.2f\n",s.id,s.nume,s.medie);
//	printf("Note (%d) : ", s.nrNote);
//	for (int i = 0; i < s.nrNote; i++) {
//		printf("%d ", s.note[i]);
//	}
//	printf("\n----------------\n");
//}
//
////functie modifica nume
//void modificaNume(struct Student* s,const char* numeNou){
//	if (s->nume!=NULL) {
//		free(s->nume);
//	}
//	s->nume = (char*)malloc(sizeof(char) * (strlen(numeNou) + 1));
//	strcpy_s(s->nume, strlen(numeNou) + 1, numeNou);
//}
//
////functie adauga nota noua
//void adaugaNota(struct Student* s, int notaNoua) {
//	int* noteNoi = (int*)malloc(sizeof(int) * (s->nrNote + 1));
//	float suma = 0;
//	if (s->note) {
//		
//		for (int i = 0; i < s->nrNote; i++) {
//			noteNoi[i] = s->note[i];
//			suma += noteNoi[i];
//		}
//	}
//	noteNoi[s->nrNote] = notaNoua;
//	suma+=notaNoua;
//
//	free(s->note);
//	s->note = noteNoi;
//	s->nrNote++;
//	s->medie = suma / s->nrNote;
//}
//
////dezalocare
//void dezalocare(struct Student* s) {
//	if (s->nume != NULL) {
//		free(s->nume);
//		s->nume = NULL;
//	}
//	if (s->note != NULL) {
//		free(s->note);
//		s->note = NULL;
//	}
//	s->medie = 0;
//	s->nrNote = 0;
//}
//
//int main() {
//	struct Student s;
//	int note[] = { 10,9,8,5 };
//	s = initializare(1, "Ana", note,4);
//	afisare(s);
//
//	modificaNume(&s, "Maria");
//	afisare(s);
//
//	adaugaNota(&s, 7);
//	afisare(s);
//
//	dezalocare(&s);
//	afisare(s);
//	return 0;
//}