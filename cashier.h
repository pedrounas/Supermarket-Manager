#ifndef CASHIER_H
#define CASHIER_H

#include <stdlib.h>

#include "client.h"
#include "queue.h"
#include "minHeap.h"

typedef struct
{
	Bool priority;
	union {
    	Queue *normalQueue;
    	HEAPMIN *priorityQueue;
    } queue;
    int eta;
    int numberOfClients;
    int products;
    int waitingTime;
    int id;
    int speed;
    int currentClients;
} Cashier;

int randomNumber();
int randomNumber_();
void updateEta(Cashier *c, int n);
void addClient(Cashier *c, Client *client);
void updateProducts(Cashier *c, int n);
void updateWaitingTime(Cashier *c, int n);
void removeClient(Cashier *c);
void *getQueue(Cashier *c);
int getId(Cashier *c);
int getEta(Cashier *c);
int getClients(Cashier *c);
int getCurrentClients(Cashier *c);
int getProducts(Cashier *c);
int getWaitingTime(Cashier *c);
int getSpeed(Cashier *c);
Bool isEmpty(Cashier *c);
void printCashier(Cashier *c);
void free_cashier(Cashier *c);

#endif