#ifndef MINHEAP_H
#define MINHEAP_H

/*-----------------------------------------------------------------------*\
|  Exemplo de implementacao de fila de prioridade (por heap de mínimo)    |
|                                                                         |
|   A.P.Tomás, CC2001 (material para prova pratica), DCC-FCUP, 2017       |
|   Last modified: 2017.12.18                                             |
|   Modificado por Frederico Lopes e Pedro Unas.                          |
\*-----------------------------------------------------------------------*/

#include "client.h"

typedef struct heapMin {
  int sizeMax, size;
  Client **clients;
} HEAPMIN;

// Inteiro para controlar a ordem na heap por ordem de entrada caso
// os elementos sejam iguais

//---------  protótipos das funções disponíveis --------------------

HEAPMIN *build_heap_min(int n);
void insert(Client* c, HEAPMIN *q);
Client* firstHeap(HEAPMIN *q);
Client* extractMin(HEAPMIN *q);   // retorna v
void decreaseKey(Client* c, int pos,HEAPMIN *q);
int heap_isEmpty(HEAPMIN *q);   // retorna 1 ou 0

void write_heap(HEAPMIN *q);
void destroy_heap(HEAPMIN *q);


//----------------- definição das funções e macros ---------------------

#define POSINVALIDA 0

#define LEFT(i) (2*(i))
#define RIGHT(i) (2*(i)+1)
#define PARENT(i) ((i)/2)

#endif
