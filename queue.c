#include <stdio.h>
#include <stdlib.h>

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

    q->queue = (void *)malloc(sizeof(void*) * n);
    if (q->queue == NULL)
        queue_exit_error("sem memoria");

    for(int i=0; i<n; i++)
        q->queue[i] = NULL;

    q->nmax = n;
    q->start = -1;
    q->end = 0;

    return q;
}

// libertar fila
void free_queue(Queue *q)
{
    if (q == NULL)
        queue_exit_error("fila mal construida");

    if(q->queue != NULL){
        for(int i=0; i<q->nmax; i++)
            if(q->queue[i] != NULL)
                free(q->queue[i]);

        free(q->queue);
    }
    free(q);
}

// colocar valor na fila
void enqueue(void* v, Queue *q)
{
    if (q == NULL)
        queue_exit_error("fila mal construida");
    else if (queue_is_full(q) == TRUE)
        queue_exit_error("fila sem lugar");

    if (queue_is_empty(q) == TRUE)
        q->start = q->end; // fila fica com um elemento

    q->queue[q->end] = v;
    q->end = (q->end + 1) % (q->nmax);
}

// retirar valor na fila
void* dequeue(Queue *q)
{
    if (q == NULL)
        queue_exit_error("fila mal construida");
    else if (queue_is_empty(q) == TRUE) {
        queue_exit_error("fila sem valores");
    }
    void* aux = q->queue[q->start];
    q->queue[q->start] = NULL;

    q->start = (q->start + 1) % (q->nmax);

    if (q->start == q->end)
    { // se só tinha um elemento
        q->start = -1;
        q->end = 0;
    }

    return aux;
}

// verificar se a fila está vazia
Bool queue_is_empty(Queue *q)
{
    if (q == NULL)
        queue_exit_error("fila mal construida");

    if (q->start == -1)
        return TRUE;

    return FALSE;
}

// verificar se a fila não admite mais elementos
Bool queue_is_full(Queue *q)
{
    if (q == NULL)
        queue_exit_error("fila mal construida");

    if (q->end == q->start)
        return TRUE;

    return FALSE;
}

void* first(Queue *q) {
    if (q == NULL)
        queue_exit_error("fila mal construida");
    else if (queue_is_empty(q) == TRUE)
        queue_exit_error("fila sem valores");

    return q->queue[q->start];
}

int length(Queue *q){
    if (q == NULL)
        queue_exit_error("fila mal construida");

    if(queue_is_empty(q) == TRUE)
        return 0;
    else if(queue_is_full(q) == TRUE)
        return q->nmax;

    if(q->start > q->end)
        return q->start - q->end;

    return q->end - q->start;
}