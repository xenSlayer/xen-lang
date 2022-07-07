CC = g++
CFLAGS = -c -std=c99 -g
LDFLAGS = -g
SRC = ${wildcard src/*.cc}
HDR = ${wildcard include/*.h}
OBJ = ${SRC:.cc=.o}
EXEC = xen
CDIR = ${CMAKE_CURRENT_BINARY_DIR}

all: ${SRC} ${OBJ} ${EXEC}
	make clean

debug: all
debug: CFLAG += -DDEBUG

FLEX = flex
LEXER_FILES := ${wildcard lexer/*.l}
LEXER_OUT = ${wildcard lexer/*.yy.*}
lexer: $(LEXER_FILES)
	$(FLEX) $(LEXER_FILES)

$(EXEC): ${OBJ}
	$(CC) ${LDFLAGS} $^ -o $@

%.o: %.c ${HDR}
	${CC} ${CFLAGS} $< -o $@

clean:
	rm ./src/*.o
