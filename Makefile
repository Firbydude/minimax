.SUFFIXES: .c .o
CC = gcc
EXEC = minimax
CCFLAGS = -std=c99 -pedantic -g -Wall
OBJS = func.o minimax.o

${EXEC}: ${OBJS}
	${CC} ${CCFLAGS} -lm -o ${EXEC} ${OBJS}

.c.o:
	${CC} ${CCFLAGS} -c $<

run: ${EXEC}
	./${EXEC}
    
clean:
	rm -f ${EXEC} ${OBJS}

minimax.o: minimax.c

func.o: func.c func.h
