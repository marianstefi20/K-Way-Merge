#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include "heap.h"
typedef int Date;
typedef struct Element {
    Date valoare;
    struct Element* urmator;
} Element;

typedef struct heapElement {
	int value;
	int list_index;
} heapElement;

void Afisare(Element* cap) {
    if(cap == NULL)
        printf("Hopa mitica! \n");
    while (cap != NULL) {
        printf("Valoare: %d\n", cap->valoare);
        cap = cap->urmator;
    }
}

void InserareInceput(Element** cap, Date val) {
    Element *elem;
    elem = (Element*)malloc(sizeof(Element));
    elem->valoare = val;
    // legare nod in lista
    elem->urmator = *cap;
    // mutarea capului listei
    *cap = elem; 
}

void StergereElement(Element ** cap) {
    Element *tmp = *cap;            
    if (tmp == NULL) return;             
    *cap = tmp->urmator;                  
    free (tmp);                         
}

/* Codul de mai jos ne va oferi un comportament ciudat
-------------------------------------------------------->
void creare_k_liste(Element ***array, int nrListe) {
    int j;
    *array = (Element**)malloc(nrListe * sizeof(Element*));
    for(j=0;j<nrListe;j++) {
        *array[j] = NULL;
    }
    for(j=0;j<nrListe;j++) {
        int nrElem, i, elem;
        printf("Numarul de elemente din lista[%d]: ", j);
        scanf("%d", &nrElem);
        for(i=0;i<nrElem;i++) {
            printf("El[%d]=", i);
            scanf("%d", &elem);
            InserareInceput(array[j], elem);
        }
    }
    for(j=0;j<nrListe;j++) {
        Afisare(*array[j]);
    }
}
<------------------------------------------------------------*/

Element **create_array(int nrListe, int* sumElemente) {
    int j;
    Element **array = (Element**)malloc(sizeof(Element *) * nrListe);
    for(j=0;j<nrListe;j++) {
        int nrElem, i, elem;
        printf("Numarul de elemente din lista[%d]: ", j);
        scanf("%d", &nrElem);
        (*sumElemente) = (*sumElemente) + nrElem; // facem suma pentru a determina dimensiunea totala a vectorului final
        for(i=0;i<nrElem;i++) {
            printf("El[%d]=", i);
            scanf("%d", &elem);
            InserareInceput(&array[j], elem);
        }
    }
    return array;
}

int main() {
    // declarare lista vida
    Element **array;
    int nrListe, j, sumElemente = 0;
	
    printf("Cate liste vrei?");
    scanf("%d", &nrListe);
    array = create_array(nrListe, &sumElemente);
    // Afisare liste
    for(j=0;j<nrListe;j++) {
		printf("\n Lista [%d]\n", j);
		Afisare(array[j]);
	}
    printf("\n");
    
    
    // Definim un nou heap in care vom tine toate elementele
    struct heapStruct *h;
    h = initHeap();
    // Testam adaugarea primelor elemente din fiecare lista
    for(j=0;j<nrListe;j++) 
		insert(h, array[j]->valoare, j);
    printHeap(h);
	
	// Incepem sa punem primul element de pe heap primul
	int *result;
	result = (int*)malloc(sizeof(int)*sumElemente);
	int c = 0;
	printf("Marimea la heap: %d", nrListe);
	printf("Cate elemente vom avea: %d", sumElemente);
	while( nrListe > 0) {         
		heapElement min;
		int i, k;
		min = removeMin(h);
		i = min.list_index;
		k = min.value;
		printf("\n [Valoare|index] = [%d|%d]\n", k, i);
		nrListe--;
		// Trebuie sa stergem nodul cu indexul i
		StergereElement(&array[i]);
		
		
		result[c++] = k;
		if (array[i] != NULL && c < 100)  {
			insert(h, array[i]->valoare, i);         
			nrListe++;
		}
	}
	
	int i;
	printf("\n");
	for(i=0;i<sumElemente;i++) 
		printf("%d  ", result[i]);
	printf("\n");
	
	// In absenta lui free apareau anumite erori interesante
    free(array);

    return 0;
}
