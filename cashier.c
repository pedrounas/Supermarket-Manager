#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "queue.h"
#include "client.h"
#include "cashier.h"

int randomNumber()
{
    int i;
    i = rand() % 10;
    if (i == 0)
        i++;
    return i;
}

int randomNumber_()
{
    int i;
    i = rand() % 20;
    if (i == 0)
        i++;
    return i;
}

void updateEta(Cashier *c, int n)
{
    c->eta = n;
}

void addClient(Cashier *c,Client *client)
{
    c->numberOfClients++;
    c->currentClients++;
    enqueue((void *)client, c->queue);
}

void updateProducts(Cashier *c, int n)
{
    c->products += n;
}

void updateWaitingTime(Cashier *c, int n)
{
    c->waitingTime += n;
}

void removeClient(Cashier *c)
{
    dequeue(c->queue);
    c->currentClients--;
}

Queue *getQueue(Cashier *c)
{
    return c->queue;
}

int getId(Cashier *c)
{
    return c->id;
}

int getEta(Cashier *c)
{
    return c->eta;
}

int getClients(Cashier *c)
{
    return c->numberOfClients;
}

int getCurrentClients(Cashier *c)
{
    return c->currentClients;
}

int getProducts(Cashier *c)
{
    return c->products;
}

int getWaitingTime(Cashier *c)
{
    return c->waitingTime;
}

int getSpeed(Cashier *c)
{
    return c->speed;
}

Bool isEmpty(Cashier *c)
{
    return c->currentClients == 0 ? TRUE : FALSE;
}

void printCashier(Cashier *c)
{
    printf("Caixa %d (%d): ", c->id, c->eta);

    //if(length(c->queue) != 0)
    for (int i = 0; (Client *)(c->queue->queue[i]) != NULL; i++)
        print_client((Client *)(c->queue->queue[i]));

    printf("\n");
}