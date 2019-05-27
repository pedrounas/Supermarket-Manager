#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "queue.h"
#include "client.h"
#include "cashier.h"
#include "minHeap.h"

static void cashier_exit_error(char *msg);

static void cashier_exit_error(char *msg)
{
    fprintf(stderr, "Error: %s.\n", msg);
    exit(EXIT_FAILURE);
}

int randomNumber(int n)
{
    return rand() % n + 1;
}

int randomNumber_()
{
    return rand() % 20 + 1;
}

void updateEta(Cashier *c, int n)
{
    if (c == NULL)
        cashier_exit_error("caixa mal construida");

    c->eta = n;
}

void addClient(Cashier *c,Client *client)
{
    if (c == NULL)
        cashier_exit_error("caixa mal construida");

    c->numberOfClients++;
    c->currentClients++;
    if(c->priority)
        insert((void *)client, c->queue.priorityQueue);
    else
        enqueue((void *)client, c->queue.normalQueue);
}

void updateProducts(Cashier *c, int n)
{
    if (c == NULL)
        cashier_exit_error("caixa mal construida");

    c->products += n;
}

void updateWaitingTime(Cashier *c, int n)
{
    if (c == NULL)
        cashier_exit_error("caixa mal construida");

    c->waitingTime += n;
}

void removeClient(Cashier *c)
{
    if (c == NULL)
        cashier_exit_error("caixa mal construida");

    if(c->priority)
        free(extractMin(c->queue.priorityQueue));
    else
        free((Client *)dequeue(c->queue.normalQueue));

    c->currentClients--;
}

void *getQueue(Cashier *c)
{
    if (c == NULL)
        cashier_exit_error("caixa mal construida");

    if(c->priority)
        return (void*)c->queue.priorityQueue;

    return (void*)c->queue.normalQueue;
}

int getId(Cashier *c)
{
    if (c == NULL)
        cashier_exit_error("caixa mal construida");

    return c->id;
}

int getEta(Cashier *c)
{
    if (c == NULL)
        cashier_exit_error("caixa mal construida");

    return c->eta;
}

int getClients(Cashier *c)
{
    if (c == NULL)
        cashier_exit_error("caixa mal construida");

    return c->numberOfClients;
}

int getCurrentClients(Cashier *c)
{
    if (c == NULL)
        cashier_exit_error("caixa mal construida");

    return c->currentClients;
}

int getProducts(Cashier *c)
{
    if (c == NULL)
        cashier_exit_error("caixa mal construida");

    return c->products;
}

int getWaitingTime(Cashier *c)
{
    if (c == NULL)
        cashier_exit_error("caixa mal construida");

    return c->waitingTime;
}

int getSpeed(Cashier *c)
{
    if (c == NULL)
        cashier_exit_error("caixa mal construida");

    return c->speed;
}

Bool isEmpty(Cashier *c)
{
    if (c == NULL)
        cashier_exit_error("caixa mal construida");

    return c->currentClients == 0 ? TRUE : FALSE;
}

void printCashier(Cashier *c)
{
    if (c == NULL)
        cashier_exit_error("caixa mal construida");

    printf("Caixa %d (%d): \n", c->id, c->eta);

    //if(length(c->queue) != 0)
    if(c->priority){
        printf("Printing priority queue (order is not correct)\n");
        for (int i = 1; i <= c->queue.priorityQueue->size; i++)
            print_client((Client *)(c->queue.priorityQueue->clients[i]));
    }
    else{
        printf("Printing normal queue\n");
        for (int i = 0; (Client *)(c->queue.normalQueue->queue[i]) != NULL; i++)
            print_client((Client *)(c->queue.normalQueue->queue[i]));
    }
}

void free_cashier(Cashier *c){
    if (c == NULL)
        cashier_exit_error("caixa mal construida");

    if(c->priority)
        destroy_heap(c->queue.priorityQueue);
    else
        free_queue(c->queue.normalQueue);

    free(c);
}