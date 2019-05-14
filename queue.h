#ifndef QUEUE_H
#define QUEUE_H

typedef enum
{
    FALSE,
    TRUE
} Bool;

typedef struct _Queue
{
    int start, end, nmax;
    void** queue;
} Queue;

// criar fila com capacidade para n inteiros
Queue *mk_empty_queue(int n);
// colocar valor na fila
void enqueue(void* v, Queue *q);
// retirar valor na fila
void* dequeue(Queue *q);
// verificar se a fila está vazia
Bool queue_is_empty(Queue *q);
// verificar se a fila não admite mais elementos
Bool queue_is_full(Queue *q);
// liberta fila
void free_queue(Queue *q);

// retorna o primeiro elemento
void* first(Queue *q);
// retorna o comprimento da fila
int length(Queue *q);

// retorna uma lista a partir da fila
// FILA *lista_fila(Queue *q);
// verifica se é fila
// Bool e_fila(Queue *q);

#endif