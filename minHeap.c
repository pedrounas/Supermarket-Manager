#include <stdio.h>
#include <stdlib.h>

#include "minHeap.h"
#include "client.h"

static void heapify(int i,HEAPMIN *q);
static void swap(int i,int j,HEAPMIN *q);
static int compare(int i, int j, HEAPMIN *q);

static int compare(int i, int j, HEAPMIN *q){
  if (q -> clients[i]->items == q -> clients[j]->items){
    if(q -> clients[i]->entrance < q -> clients[j]->entrance)
      return -1;
    else if(q -> clients[i]->entrance == q -> clients[j]->entrance)
      return 0;
    else
      return 1;
  }

  if(q -> clients[i]->items < 10 && q -> clients[j]->items < 10){
    if(q -> clients[i]->entrance < q -> clients[j]->entrance)
      return -1;
    else
      return 1;
  }

  if(q -> clients[i]->items < 10)
    return -1;

  if(q -> clients[j]->items < 10)
    return 1;

  if(q -> clients[i]->entrance < q -> clients[j]->entrance)
    return -1;

  return 1;
}

Client* firstHeap(HEAPMIN *q){
  return q->clients[1];
}

Client* extractMin(HEAPMIN *q) {
  Client* vertv = q -> clients[1];
  swap(1,q->size,q);
  q -> size--;
  heapify(1,q);
  return vertv;
}

void decreaseKey(Client* c, int pos, HEAPMIN *q){
  while(pos > 1 && compare(pos,PARENT(pos),q) < 0){
    swap(pos,PARENT(pos),q);
    pos = PARENT(pos);
  }
}


static void heapify(int i,HEAPMIN *q) {
  // para heap de minimo
  int l, r, smallest;
  l = LEFT(i);
  if (l > q -> size) l = i;
  r = RIGHT(i);
  if (r > q -> size) r = i;

  smallest = i;
  if (compare(l,smallest,q) < 0)
    smallest = l;
  if (compare(r,smallest,q) < 0)
    smallest = r;

  if (i != smallest) {
    swap(i,smallest,q);
    heapify(smallest,q);
  }
}

static void swap(int i,int j,HEAPMIN *q){
  Client* aux;
  aux = q -> clients[i];
  q -> clients[i] = q -> clients[j];
  q -> clients[j] = aux;
}



HEAPMIN *build_heap_min(int n){
  // supor que vetor vec[.] guarda elementos nas posições 1 a n
  // cria heapMin correspondente em tempo O(n)
  HEAPMIN *q = (HEAPMIN *)malloc(sizeof(HEAPMIN));
  q -> clients = (Client **) malloc(sizeof(Client*)*(n+1));
  q -> sizeMax = n; // posicao 0 nao vai ser ocupada
  q -> size = 0;

  return q;
}


void insert(Client* c, HEAPMIN *q)
{
  if (q -> sizeMax == q -> size) {
    fprintf(stderr,"Heapmin is full\n");
    exit(EXIT_FAILURE);
  }
  q -> size++;
  q -> clients[q->size] = c;
  decreaseKey(c, q->size, q);   // diminui a chave e corrige posicao se necessario
}


int heap_isEmpty(HEAPMIN *q){
  if (q -> size == 0) return 1;
  return 0;
}


// --------- auxiliar para ver conteudo  ---------------------
void write_heap(HEAPMIN *q){
  int i;

  printf("Max size: %d\n", q -> sizeMax);
  printf("Current size: %d\n", q -> size);

  printf("(Vert,Key)\n---------\n");
  for(i=1; i <= q -> size; i++)
    printf("(%d,%d)\n",q->clients[i]->id,q->clients[i]->entrance);
}

void destroy_heap(HEAPMIN *q){
  if (q != NULL) {
    free(q -> clients);
    free(q);
  }
}
