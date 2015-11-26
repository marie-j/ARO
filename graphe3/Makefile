CC = gcc
CFLAGS = -Wall
CFLAGS += -std=c99

LDFLAGS = -g  

EXE = shortdistance

all : realclean ${EXE}

shortdistance : shortdistance.o graphe.o
	${CC} ${LDFLAGS} -o $@ $^

shortdistance.o : shortdistance.c
	${CC} ${CFLAGS} -c $<

graphe.o : graphe.c
	${CC} ${CFLAGS} -c $<

.PHONY: clean realclean

clean: 
	rm -rf *.o *~ || true

realclean: clean
	rm -rf ${EXE}
