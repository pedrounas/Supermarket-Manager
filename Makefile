INTERM=queue.c queue.h client.c client.h cashier.c cashier.h supermarket.c
PROGRAM=./supermarket
CFLAGS=-Wall -g -fsanitize=address
CC = gcc
RM = rm -f


all: $(PROGRAM)

$(PROGRAM): $(INTERM)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(INTERM)

clean:
	$(RM) $(PROGRAM)
