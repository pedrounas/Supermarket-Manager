#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "queue.h"
#include "client.h"
#include "cashier.h"

int randomNumber()
{
    int i;
    srand((unsigned)time(NULL));
    i = rand() % 5;
    return i;
}

void updateEta(Cashier *c, int n)
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
    return c->products == 0 ? TRUE : FALSE;
}

void printCashier(Cashier *c)
{
    printf("Caixa %d (%d): ", c->id, c->eta);


    for(int i=0; c->queue->queue[i + 1] != NULL; i++)
        print_client(c->queue->queue[i]);

    printf("\n");
}