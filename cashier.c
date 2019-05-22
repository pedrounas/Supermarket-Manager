#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "queue.h"
#include "client.h"
#include "cashier.h"

static void cashier_exit_error(char *msg);

static void cashier_exit_error(char *msg)
{
    fprintf(stderr, "Error: %s.\n", msg);
    exit(EXIT_FAILURE);
}

int randomNumber(int n)
{
    int i;
    i = rand() % n;
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
    enqueue((void *)client, c->queue);
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

    free((Client *)dequeue(c->queue));
    c->currentClients--;
}

Queue *getQueue(Cashier *c)
{
    if (c == NULL)
        cashier_exit_error("caixa mal construida");

    return c->queue;
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
    for (int i = 0; (Client *)(c->queue->queue[i]) != NULL; i++)
        print_client((Client *)(c->queue->queue[i]));
}

void free_cashier(Cashier *c){
    if (c == NULL)
        cashier_exit_error("caixa mal construida");

    free_queue(c->queue);

    free(c);
}