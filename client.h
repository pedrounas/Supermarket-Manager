#ifndef CLIENT_H
#define CLIENT_H

typedef struct _Client
{
    int id, items, entrance;
} Client;

Client *mk_client(int id, int items, int entrada);
int id(Client *c);
int items(Client *c);
int entrance(Client *c);
void print_client(Client *c);

#endif
