#include <stdio.h>

#include "queue.h"
#include "client.h"
#include "cashier.h"

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
    for (int i = 0; i <= size; i++)
    {
        printCashier(list[i]);
    }
}

void getResults(Cashier **list)
{
    for (int i = 0; i <= size; i++)
    {
        printf("Cashier %d with %d speed\n", list[i]->id, list[i]->speed);
        if (list[i]->numberOfClients != 0)
            printf("%d clients serviced, %.2f products per client\n", list[i]->numberOfClients, (float)(list[i]->products / list[i]->numberOfClients));
        else
            printf("%d clients serviced\n", list[i]->numberOfClients);
    }
}

/* TODO move_clients(Cashier **list) */

void simulation(rate, productRate, numberOfCashiers, numberOfTurns)
{
    Cashier *list[size];
    memset(&list, 0, sizeof list);
    int i;
    for (i = 0; i < numberOfTurns; i++)
    {
        printf("Cycle %d\n", i);

        moveClients(i, list);

        int random = randomNumber();

        if (random <= (int)rate / 100)
        {
            int numberOfProducts = randomNumber();
            Cliente *c;
            c->entrada = i;
            c->items = numberOfProducts;

            printf("New client with %d products entered at %d\n", numberOfProducts, i);

            int cashierId = chooseCashier(list);

            enqueue(c->items, list[cashierId]->queue);
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
    print("Insira a afluência, apetencia, numero de caixas e numero de ciclos: ");
    sscanf("%d %d %d %d", rate, productRate, numberOfCashiers, numberOfTurns);
    size = numberOfCashiers;
    printf("\n");
    simulation(rate, productRate, numberOfCashiers, numberOfTurns);
}