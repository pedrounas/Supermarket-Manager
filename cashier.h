#include <stdlib.h>

#include "queue.h"

typedef struct
{
    Queue *queue;
    int eta;
    int numberOfClients;
    int products;
    int waitingTime;
    int id;
    int speed = randomNumber();
} Cashier;

int randomNumber();
void changeEta(Cashier *c, int n);
void addClient(Cashier *c);
void updateProducts(Cashier *c, int n);
void updateWaitingTime(Cashier *c, int n);
void removeClient(Cashier *c);
Queue *getQueue(Cashier *c);
int getId(Cashier *c);
int getEta(Cashier *c);
int getClients(Cashier *c);
int getProducts(Cashier *c);
int getWaitingTime(Cashier *c);
float getAverage(Cashier *c);
Bool isEmpty(Cashier *c);
char *printCashier(Cashier *c);