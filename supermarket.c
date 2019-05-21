#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "queue.h"
#include "client.h"
#include "cashier.h"

#define MAX_CLIENTS 32

Cashier **globalList;
int size;

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
    {
        printCashier(list[i]);
    }
}

void getResults(Cashier **list)
{
    for (int i = 0; i < size; i++)
    {
        printf("Cashier %d with %d speed\n", list[i]->id, list[i]->speed);
        if (list[i]->numberOfClients != 0)
            printf("%d clients serviced, %.2f products per client\n", list[i]->numberOfClients, (float)(list[i]->products / list[i]->numberOfClients));
        else
            printf("%d clients serviced\n", list[i]->numberOfClients);
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
        addClient(cashier);
        updateWaitingTime(cashier, (i - entrance(c)));
        removeClient(cashier);
        printf("Client went through cashier %c\n", getId(cashier));
    }
}

void moveClients(int i, Cashier **list)
{
    for (int j = 0; j < size; j++)
    {
        if (isEmpty(list[j]))
            updateEta(list[j], i);
        else
            handleFirst(i, list[i]);
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
        c->queue = mk_empty_queue(size);
        c->eta = 0;
        c->numberOfClients = 0;
        c->products = 0;
        c->waitingTime = 0;
        c->id = i;
        c->speed = randomNumber();
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
        printf("Cycle %d\n", i);

        moveClients(i, list);

        int random = randomNumber();

        if (random <= (int)rate / 100)
        {
            int numberOfProducts = randomNumber();
            Client *c = mk_client(i*4,i, numberOfProducts);

            printf("New client with %d products entered at %d\n", numberOfProducts, i);

            int cashierId = chooseCashier(list);
            int itemList = items(c);
            enqueue(c, list[cashierId]->queue);
            updateProducts(list[cashierId], itemList);
        }

        showCashiers(list);
    }

    printf("Simulation ended\n");

    i++;
    while (emptyCashiers(list) == TRUE)
    {
        printf("Cycle %d\n", i);
        moveClients(i, list);
        showCashiers(list);
        i++;
    }

    getResults(list);
}

int main()
{
    int rate, productRate, numberOfCashiers, numberOfTurns;
    printf("Insira a afluência, apetencia, numero de caixas e numero de ciclos: ");
    scanf("%d %d %d %d", &rate, &productRate, &numberOfCashiers, &numberOfTurns);
    size = numberOfCashiers;
    printf("\n");
    simulation(rate, productRate, numberOfCashiers, numberOfTurns);
}