#include <stdio.h>
#include <stdlib.h>

#define MAX_CVOROVA 10000

typedef struct Cvor{
    int vrh;
    int tezina;
    struct Cvor *sledeci;
}Cvor;

typedef struct Graf{
    int brojVrhova;
    Cvor **listePovezanosti;
}Graf;

typedef struct Grana{
    int izvor;
    int cilj; 
    int tezina;
}Grana;

Cvor *kreirajCvor(int v, int tezina){
    Cvor *noviCvor=malloc(sizeof(Cvor));
    noviCvor->vrh=v;
    noviCvor->tezina=tezina;
    noviCvor->sledeci=NULL;
    return noviCvor;
}

Graf *kreirajGraf(int vrhovi){
    Graf *graf=malloc(sizeof(Graf));
    graf->brojVrhova=vrhovi;

    graf->listePovezanosti=malloc(vrhovi*sizeof(Cvor*));

    for (int i=0;i<vrhovi;i++)
        graf->listePovezanosti[i]=NULL;

    return graf;
}

void dodajGrana(Graf *graf, int izvor, int cilj, int tezina){
    Cvor *noviCvor=kreirajCvor(cilj, tezina);
    noviCvor->sledeci=graf->listePovezanosti[izvor];
    graf->listePovezanosti[izvor]=noviCvor;

    noviCvor=kreirajCvor(izvor, tezina);
    noviCvor->sledeci=graf->listePovezanosti[cilj];
    graf->listePovezanosti[cilj]=noviCvor;
}

int uporediIvice(const void *a, const void *b){
    Grana *granaA=(Grana*)a;
    Grana *granaB=(Grana*)b;
    return granaA->tezina - granaB->tezina;
}

int nadji(int roditelj[], int i){
    if (roditelj[i] == i)
        return i;
    return roditelj[i] = nadji(roditelj, roditelj[i]);
}

void unija(int roditelj[], int x, int y){
    int korenX = nadji(roditelj, x);
    int korenY = nadji(roditelj, y);
    roditelj[korenX] = korenY;
}

void KruskalMST(Graf *graf, int brojGrana, Grana *ivice){
    qsort(ivice, brojGrana, sizeof(ivice[0]), uporediIvice);

    int *roditelj=malloc(graf->brojVrhova*sizeof(int));
    for (int i=0;i<graf->brojVrhova;i++)
        roditelj[i]=i;

    Grana *rezultat=malloc((graf->brojVrhova-1)*sizeof(Grana));
    int e=0;
    int i=0;
    int ukupno=0;

    while(e<graf->brojVrhova-1 && i<brojGrana){
        Grana sledecaGrana=ivice[i++];

        int x=nadji(roditelj, sledecaGrana.izvor);
        int y=nadji(roditelj, sledecaGrana.cilj);

        if(x!=y){
            rezultat[e++]=sledecaGrana;
            unija(roditelj,x,y);
        }
    }

    printf("Minimalno razapinjajuće stablo (MST):\n");
    for (i=0;i<e;i++){
        printf("%d -- %d == %d\n", rezultat[i].izvor, rezultat[i].cilj, rezultat[i].tezina);
        ukupno=ukupno+rezultat[i].tezina;
    }
    printf("Ukupna tezina je: %d\n",ukupno);
    free(rezultat);
    free(roditelj);
}

int jeBezbedno(int v, Graf *graf, int put[], int poz) {
    Cvor *temp = graf->listePovezanosti[put[poz - 1]];
    while (temp) {
        if (temp->vrh == v) {
            for (int i = 0; i < poz; i++) {
                if (put[i] == v) {
                    return 0;
                }
            }
            return 1;
        }
        temp = temp->sledeci;
    }
    return 0;
}

int hamCiklusUtil(Graf *graf, int put[], int poz) {
    if (poz == graf->brojVrhova) {
        Cvor *temp = graf->listePovezanosti[put[poz - 1]];
        while (temp) {
            if (temp->vrh == put[0]) {
                return 1;
            }
            temp = temp->sledeci;
        }
        return 0; 
    }

    for (int v = 1; v < graf->brojVrhova; v++) {
        if (jeBezbedno(v,graf, put, poz)) {
            put[poz] = v;

            if (hamCiklusUtil(graf, put, poz + 1)) {
                return 1;
            }

            put[poz] = -1;
        }
    }
    return 0;
}

void hamCiklus(Graf *graf){
    int *put=malloc(graf->brojVrhova * sizeof(int));
    for(int i=0;i<graf->brojVrhova;i++)
        put[i] = -1;

    put[0]=0;
    if(hamCiklusUtil(graf, put, 1) == 0){
        printf("\nHamiltonov ciklus ne postoji\n");
        free(put);
        return;
    }
    printf("Hamiltonov ciklus postoji:\n");
    for (int i=0;i<graf->brojVrhova;i++)
        printf(" %d ", put[i]);
    printf(" %d \n", put[0]);

    free(put);
}

void generisi(Graf* graf, Grana ivice[], int* brojGranaBrojac, int izvor, int cilj, int tezina) {
    dodajGrana(graf, izvor, cilj, tezina);
    ivice[*brojGranaBrojac].izvor = izvor;
    ivice[*brojGranaBrojac].cilj = cilj;
    ivice[*brojGranaBrojac].tezina = tezina;
    (*brojGranaBrojac)++;
}

int main(){
    
    int V = 8; 
    int E =0;  

    Graf *graf=kreirajGraf(V);
    Grana *ivice=malloc(V* sizeof(Grana));

    generisi(graf, ivice, &E, 0, 1, 10);
    generisi(graf, ivice, &E, 1, 2, 15);
    generisi(graf, ivice, &E, 2, 3, 10);
    generisi(graf, ivice, &E, 3, 4, 5);
    generisi(graf, ivice, &E, 4, 5, 20);
    generisi(graf, ivice, &E, 5, 6, 25);
    generisi(graf, ivice, &E, 6, 7, 30);
    generisi(graf, ivice, &E, 7, 0, 35);  // Dodajemo granu koja zatvara ciklus


    KruskalMST(graf, E, ivice);

    hamCiklus(graf);

    free(ivice);
    for(int i=0;i<V;i++){
        Cvor *temp=graf->listePovezanosti[i];
        while(temp){
            Cvor *zaOslobadjanje=temp;
            temp=temp->sledeci;
            free(zaOslobadjanje);
        }
    }
    free(graf->listePovezanosti);
    free(graf);

    return 0;
}
