CC = g++
CFLAGS = -c -std=c99 -g
LDFLAGS = -g
SRC = ${wildcard src/*.cc}
HDR = ${wildcard include/*.h}
OBJ = ${SRC:.cc=.o}
EXEC = xen

all: ${SRC} ${OBJ} ${EXEC}
	make clean

debug: all
debug: CFLAG += -DDEBUG

FLEX = flex++
files := ${wildcard lexer/*.l}
LEXER_SRC = ${wildcard lexer/*.cc}
build-lexer: $(files)
	$(FLEX) $(files)
	${CC} ${LEXER_SRC} -o lexer


$(EXEC): ${OBJ}
	$(CC) ${LDFLAGS} $^ -o $@

%.o: %.c ${HDR}
	${CC} ${CFLAGS} $< -o $@

clean:
	rm ./src/*.o