#ifndef MINHEAP_H
#define MINHEAP_H

typedef struct qnode {
  int vert, vertkey;
} QNODE;

typedef struct heapMin {
  int sizeMax, size;
  QNODE *a;
  int *pos_a;
} HEAPMIN;

//---------  protótipos das funções disponíveis --------------------

HEAPMIN *build_heap_min(int v[], int n);
void insert(int v, int key, HEAPMIN *q);
int extractMin(HEAPMIN *q);   // retorna v
void decreaseKey(int v, int newkey, HEAPMIN *q);
int heap_isEmpty(HEAPMIN *q);   // retorna 1 ou 0

void write_heap(HEAPMIN *q);
void destroy_heap(HEAPMIN *q);


//----------------- definição das funções e macros ---------------------

#define POSINVALIDA 0

#define LEFT(i) (2*(i))
#define RIGHT(i) (2*(i)+1)
#define PARENT(i) ((i)/2)

static void heapify(int i,HEAPMIN *q);
static void swap(int i,int j,HEAPMIN *q);
static int compare(int i, int j, HEAPMIN *q);
static int pos_valida(int i,HEAPMIN *q);

#endif
