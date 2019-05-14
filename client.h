#ifndef CLIENT_H
#define CLIENT_H

typedef struct _Client
{
    int items, entrance;
} Client;

Client *mk_client(int items, int entrada);
int items(Client *c);
int entrance(Client *c);
void print_client(Client *c);

#endif