#include "queue.h"

typedef struct
{
    Queue *items;
    int entrada;
} Cliente;

int numero_de_artigos(Cliente *c);
int tempo_de_entrada(Cliente *c);
void imprime_cliente(Cliente *c);
