#include <stdio.h>

#include "queue.h"

// funcao auxiliar(privada)

static void queue_exit_error(char *msg);

static void queue_exit_error(char *msg)
{
    fprintf(stderr, "Error: %s.\n", msg);
    exit(EXIT_FAILURE);
}

// criar fila com capacidade para n inteiros
Queue *mk_empty_queue(int n)
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    if (q == NULL)
        queue_exit_error("sem memoria");

    q->queue = (int *)malloc(sizeof(int) * n);
    if (q->queue == NULL)
        queue_exit_error("sem memoria");

    q->nmax = n;
    q->inicio = -1;
    q->fim = 0;
    return q;
}

// libertar fila
void free_queue(Queue *q)
{
    if (q != NULL)
    {
        free(q->queue);
        free(q);
    }
    else
        queue_exit_error("fila mal construida");
}

// colocar valor na fila
void enqueue(int v, Queue *q)
{
    if (queue_is_full(q) == TRUE)
        queue_exit_error("fila sem lugar");

    if (q->queue == NULL)
        queue_exit_error("fila mal construida");

    if (queue_is_empty(q) == TRUE)
        q->inicio = q->fim; // fila fica com um elemento
    q->queue[q->fim] = v;
    q->fim = (q->fim + 1) % (q->nmax);
}

// retirar valor na fila
int dequeue(Queue *q)
{
    int aux;
    if (queue_is_empty(q) == TRUE)
        queue_exit_error("fila sem valores");

    if (q->queue == NULL)
        queue_exit_error("fila mal construida");

    aux = q->queue[q->inicio];
    q->inicio = (q->inicio + 1) % (q->nmax);
    if (q->inicio == q->fim)
    { // se só tinha um elemento
        q->inicio = -1;
        q->fim = 0;
    }
    return aux;
}

// verificar se a fila está vazia
BOOL queue_is_empty(Queue *q)
{
    if (q == NULL)
        queue_exit_error("fila mal construida");

    if (q->inicio == -1)
        return TRUE;
    return FALSE;
}

// verificar se a fila não admite mais elementos
BOOL queue_is_full(Queue *q)
{
    if (q == NULL)
        queue_exit_error("fila mal construida");

    if (q->fim == q->inicio)
        return TRUE;
    return FALSE;
}

int primeiro(Queue *q) {
    return q->inicio;
}
