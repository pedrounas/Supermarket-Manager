#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    FALSE,
    TRUE
} Bool;

typedef struct fila
{
    int inicio, fim, nmax;
    int *queue;
} Queue;

// criar fila com capacidade para n inteiros
Queue *mk_empty_queue(int n);
// colocar valor na fila
void enqueue(int v, Queue *f);
// retirar valor na fila
int dequeue(Queue *f);
// verificar se a fila está vazia
Bool queue_is_empty(Queue *f);
// verificar se a fila não admite mais elementos
Bool queue_is_full(Queue *f);
// liberta fila
void free_queue(Queue *f);
// retorna o primeiro elemento
int primeiro(Queue *f);
// retorna o comprimento da fila
// int comprimento(Queue *f);
// retorna uma lista a partir da fila
// FILA *lista_fila(Queue *f);
// verifica se é fila
// Bool e_fila(Queue *f);
