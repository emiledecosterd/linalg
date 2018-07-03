# Variables: compilateur utilisé et fanions
CC=gcc
LDFLAGS=
CFLAGS= -g -Wall -Os

# Noms des fichiers utilisés
TARGET=linalg
SRC=$(wildcard *.c)
HEADERS =$(wildcard *.h)
OBJ=$(SRC:.c=.o)

# Compilation
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

# Fichier objets
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

# Nettoyage: on supprime tous les exécutables et objets
clean:
	rm -rf *.o

cleanall:
	rm -rf *.o $(TARGET)

