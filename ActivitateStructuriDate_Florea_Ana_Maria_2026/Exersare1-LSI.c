#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Carte {
    int id;
    char* titlu;
    float pret;
    int anPublicatie;
};
typedef struct Carte Carte;

struct Nod {
    Carte info;
    struct Nod* next;
};
typedef struct Nod Nod;

// TODO 1: Inserare la inceput 
void inserareInceput(Nod** cap, Carte c) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = c;
    nou->next = *cap;
    *cap = nou;
    
}

// TODO 2: Functie care afiseaza doar cartile publicate dupa un anumit an
void afisareCartiDupaAn(Nod* cap, int anLimita) {
    printf("Carti publicate dupa anul %d:\n", anLimita);
    while(cap != NULL) {
        if (cap->info.anPublicatie > anLimita) {
            printf("ID:%d , Titlu: %s, An: %d, Pret: %2.f\n", cap->info.id, cap->info.titlu, cap->info.anPublicatie, cap->info.pret);
        }
        cap = cap->next;
    }
}

// TODO 3: Stergem prima carte (elibereaza memoria pentru titlu si pentru nod)
void stergePrimaCarte(Nod** cap) {
    if (*cap == NULL) {
        printf("Lista este deja goala\n");
        return 0;
    }
    Nod* temp = *cap;
    *cap = (*cap)->next;
    if (temp->info.titlu) {
        free(temp->info.titlu);
    }
    free(temp);
    printf("Prima carte a fost stearsa\n");
  
}
// TODO 4: Calculam valoarea totala a stocului de carti 
float calculValoareTotala(Nod* cap) {
    float suma = 0;
    while (cap != NULL) {
        suma += cap->info.pret;
        cap = cap->next; 
    }
    return suma;
   
}

int main() {
    Nod* cap = NULL;

    // Cream o carte manual 
    Carte c1;
    c1.id = 101;
    c1.pret = 45.0;
    c1.anPublicatie = 2020;

    char* nume1 = "Invata Structuri de Date";
    c1.titlu = (char*)malloc(strlen(nume1) + 1);
    strcpy_s(c1.titlu, strlen(nume1) + 1,nume1);

    Carte c2;
    c2.id = 101;
    c2.pret = 45.0;
    c2.anPublicatie = 2020;

    char* nume2 = "Pasul 1";
    c2.titlu = (char*)malloc(strlen(nume2) + 1);
    strcpy_s(c2.titlu, strlen(nume2) + 1, nume2);

    inserareInceput(&cap, c1);
    inserareInceput(&cap, c2);

    afisareCartiDupaAn(cap, 2000);

    printf("Valoare totala stoc: %.2f\n", calculValoareTotala(cap));

    
    while (cap != NULL) {
        stergePrimaCarte(&cap);
    }

    return 0;
}