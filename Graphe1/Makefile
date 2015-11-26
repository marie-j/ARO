CC = gcc
CFLAGS = -Wall 
CFLAGS += -std=c99

LDFLAGS = -g

EXE = testAnalyseur myAnalyseur

all : realclean ${EXE}

myAnalyseur : myAnalyseur.o graphe.o
	${CC} ${LDFLAGS} -o $@ $^

myAnalyseur.o : myAnalyseur.c
	${CC} ${CFLAGS} -c $< 
	
testAnalyseur : testAnalyseur.o graphe.o
	${CC} ${LDFLAGS} -o $@ $^

testAnalyseur.o : testAnalyseur.c  
	${CC} ${CFLAGS} -c $<

graphe.o : graphe.c
	${CC} ${CFLAGS} -c $<

.PHONY: clean realclean

clean: 
	rm -rf *.o *~ || true

realclean: clean 
	rm -rf ${EXE}
