#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>

#include "queue.h"
#include "client.h"
#include "cashier.h"

#define MAX_CLIENTS 32

int size;
int currClientNumber = 1;

Bool emptyCashiers(Cashier **list)
{
    for (int i = 0; i < size; i++)
    {
        if (isEmpty(list[i]) == FALSE)
            return TRUE;
    }
    return FALSE;
}

void showCashiers(Cashier **list)
{
    for (int i = 0; i < size; i++)
        printCashier(list[i]);
    printf("\n");
}

void getResults(Cashier **list)
{
    printf("################# Information #################\n");
    for (int i = 0; i < size; i++)
    {
        printf("\nInformation about cashier %d:\n", list[i]->id);
        printf("%d clients serviced\n", list[i]->numberOfClients);
        if (list[i]->numberOfClients != 0)
            printf("%.2f products per client\n", ((float)list[i]->products / list[i]->numberOfClients));
        printf("%d products processed\n", list[i]->products);
        printf("%d products per cycle\n", list[i]->speed);
    }
}

void handleFirst(int i, Cashier *cashier)
{
    Client *c = first(cashier->queue);
    int waiting = i - getEta(cashier);
    int itemsProcessed = waiting * getSpeed(cashier);
    if (itemsProcessed >= items(c))
    {
        updateEta(cashier, (i + 1));
        updateProducts(cashier, items(c));
        updateWaitingTime(cashier, (i - entrance(c)));
        printf("Client %d went through cashier %d\n", id(c), getId(cashier));
        removeClient(cashier);
    }
}

void moveClients(int i, Cashier **list)
{
    for (int j = 0; j < size; j++)
    {
        if (isEmpty(list[j]) == TRUE)
        {
            updateEta(list[j], i);
        }
        else
            handleFirst(i, list[j]);
    }
}

int chooseCashier(Cashier **list)
{
    int minC = INT_MAX;
    int cashier = -1;
    for (int i = 0; i < size; i++)
    {
        if (isEmpty(list[i]) == TRUE)
        {
            return i;
        }
        if (getCurrentClients(list[i]) < minC)
        {
            minC = getCurrentClients(list[i]);
            cashier = i;
        }
    }
    return cashier;
}

Cashier **startCashier()
{
    Cashier **list = (Cashier **)malloc(sizeof(Cashier *) * size);
    for (int i = 0; i < size; i++)
    {
        Cashier *c = (Cashier *)malloc(sizeof(Cashier));
        c->queue = mk_empty_queue(MAX_CLIENTS);
        c->eta = 0;
        c->numberOfClients = 0;
        c->products = 0;
        c->waitingTime = 0;
        c->id = i;
        c->speed = randomNumber(5);
        c->currentClients = 0;
        list[i] = c;
    }
    return list;
}

void simulation(int rate, int productRate, int numberOfCashiers, int numberOfTurns)
{
    Cashier **list = startCashier();

    int i;

    for (i = 0; i < numberOfTurns; i++)
    {
        printf("################# Cycle %d #################\n\n", i);

        int random = randomNumber_();
        if (random <= (int)rate / 100)
        {
            int numberOfProducts = randomNumber(productRate);
            Client *c = mk_client(currClientNumber, numberOfProducts * 2, i);
            currClientNumber++;
            int cashierId = chooseCashier(list);
            printf("New client with %d products entered cashier %d at %d\n\n", numberOfProducts, cashierId,i);
            int itemList = items(c);
            addClient(list[cashierId], c);
        }
        showCashiers(list);
        moveClients(i, list);
        printf("##########################################\n\n");
    }

    printf("------------------------------------- Simulation has ended! -------------------------------------\n\n");

    i++;
    while (emptyCashiers(list) == TRUE)
    {
        printf("################# Cycle %d #################\n\n", i);
        showCashiers(list);
        moveClients(i, list);
        i++;
        printf("##########################################\n\n");
    }

    getResults(list);

    for(int i=0; i<size; i++)
        free_cashier(list[i]);

    free(list);
}

int main()
{
    srand(time(NULL));

    int rate, productRate, numberOfCashiers, numberOfTurns;
    printf("Insira a afluência, apetencia, numero de caixas e numero de ciclos: ");
    scanf("%d %d %d %d", &rate, &productRate, &numberOfCashiers, &numberOfTurns);
    size = numberOfCashiers;
    printf("\n");
    simulation(rate, productRate, numberOfCashiers, numberOfTurns);
}