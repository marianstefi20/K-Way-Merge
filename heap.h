#ifndef HEADER_FILE
#define HEADER_FILE

struct heapStruct *initHeap();
int heapSize();
struct heapStruct * initHeapfromArray(int* values, int length);
void heapify(struct heapStruct *h);
void percolateDown(struct heapStruct *h, int index);
void percolateUp(struct heapStruct *h, int index);
void insert(struct heapStruct *h, int value, int index);
struct heapElement removeMin(struct heapStruct *h);
void printHeap(struct heapStruct *h);
void swap(struct heapStruct *h, int index1, int index2);
int minimum(int a, int indexa, int b, int indexb);
void freeHeap(struct heapStruct *h);

void sort(int values[], int length);

#endif
