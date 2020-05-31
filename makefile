CC = gcc
CFLAGS = -ansi -Wall -I$(IDIR)

IDIR = ./includes/
SRCDIR = ./src/
BINDIR = ./bin/

SOURCES = $(SRCDIR)*.c

all: $(BINDIR)maestro

$(BINDIR)maestro: $(BINDIR)maestro.o $(BINDIR)card_manager.o $(BINDIR)hand_manager.o $(BINDIR)probability.o
	$(CC) $(BINDIR)maestro.o $(BINDIR)card_manager.o $(BINDIR)hand_manager.o $(BINDIR)probability.o -o $@

$(BINDIR)maestro.o: $(SRCDIR)maestro.c
	$(CC) $(CFLAGS) -c $(SRCDIR)maestro.c -o $@

$(BINDIR)card_manager.o: $(SRCDIR)card_manager.c
	$(CC) $(CFLAGS) -c $(SRCDIR)card_manager.c -o $@

$(BINDIR)hand_manager.o: $(SRCDIR)hand_manager.c
	$(CC) $(CFLAGS) -c $(SRCDIR)hand_manager.c -o $@

$(BINDIR)probability.o: $(SRCDIR)probability.c
	$(CC) $(CFLAGS) -c $(SRCDIR)probability.c -o $@

clean:
	rm ./bin/*.o ./bin/maestro
