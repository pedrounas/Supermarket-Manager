#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "cashier.h"

int randomNumber()
{
    int i;
    srand((unsigned)time(NULL));
    i = rand() % 5;
    return i;
}

void changeEta(Cashier *c, int n)
{
    c->eta += n;
}

void addClient(Cashier *c)
{
    c->numberOfClients++;
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
    return c->products == 0 ? TRUE : FALSE;
}

void printCashier(Cashier *c)
{
    printf("Caixa %d (%d): ", c->id, c->eta);
    int i = 0;
    while (c->queue->queue[i + 1] != NULL)
    {
        printf("%d ", c->queue->queue[i]);
        i++;
    }
    printf("\n");
}