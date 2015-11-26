CC = gcc
CFLAGS = -Wall
CFLAGS += -std=c99

LDFLAGS = -g  

EXE = parcours

all : realclean ${EXE}

parcours : parcours.o graphe.o
	${CC} ${LDFLAGS} -o $@ $^

parcours.o : parcours.c
	${CC} ${CFLAGS} -c $<

graphe.o : graphe.c
	${CC} ${CFLAGS} -c $<

.PHONY: clean realclean

clean: 
	rm -rf *.o *~ || true

realclean: clean
	rm -rf ${EXE}
