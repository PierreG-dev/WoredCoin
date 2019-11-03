# Specific part of the Makefile
# EXEC contient le nom des exécutables à générer, le nom est indépendant des noms de fichiers auquels le makefile fait appel
EXEC = woredCoin
# Begin generic part of the Makefile
# CC indique le compilateur utilisé
CC=gcc
# CFLAGS regroupe les options de compilation (par exemple "-Werror" transforme les Warning en Error, ne produit pas d'exécutable)
CFLAGS=-std=c99
# LDFLAGS regroupe les options de l'édition de liens
LDFLAGS=

# SRC contient la liste des fichiers sources et OBJ contient la liste des fichiers objets
SRC= $(wildcard *.c)
OBJ= $(SRC:.c =.o)

ifeq ($(DEBUG), yes)
	CFLAGS += -g
	LDFLAGS =
else
	CFLAGS += -O3 -DNDEBUG
	LDFLAGS =
endif

all : $(EXEC)

$(EXEC): block.o blockchain.o transaction.o cheater.o merkel.o sha256.o sha256_utils.o process.o main.o
	$(CC) -o $(EXEC) block.o blockchain.o transaction.o cheater.o merkel.o sha256.o sha256_utils.o process.o main.o $(LDFLAGS)

block.o: block.c
	$(CC) -o block.o -c block.c $(CFLAGS)

blockchain.o: blockchain.c
	$(CC) -o blockchain.o -c blockchain.c $(CFLAGS)

transaction.o: transaction.c
	$(CC) -o transaction.o -c transaction.c $(CFLAGS)

cheater.o: cheater.c
	$(CC) -o cheater.o -c cheater.c $(CFLAGS)

merkel.o: merkel.c
	$(CC) -o merkel.o -c merkel.c $(CFLAGS)

sha256.o: sha256.c
	$(CC) -o sha256.o -c sha256.c $(CFLAGS)

sha256_utils.o: sha256_utils.c
	$(CC) -o sha256_utils.o -c sha256_utils.c $(CFLAGS)

process.o: process.c
	$(CC) -o process.o -c process.c $(CFLAGS)

main.o: main.c block.h blockchain.h transaction.h merkel.h sha256.h sha256_utils.h cheater.h process.h config.h
	$(CC) -o main.o -c main.c $(CFLAGS)

# On utilise .PHONY au cas où clean ou mrproper soient également des nom de fichiers présents dans le répertoire
.PHONY: clean mrproper

# Permet de supprimer tous les fichiers intermédiaires
clean:
	@rm -rf *.o

#Permet de supprimer tout ce qui a été généré par le makefile
mrproper: clean
	@rm -rf $(EXEC)
# End generic part of the makefile

# List of target dependencies
main.o: block.h blockchain.h transaction.h merkel.h sha256.h sha256_utils.h cheater.h process.h config.h
block.o: block.h blockchain.h transaction.h merkel.h sha256.h sha256_utils.h cheater.h process.h config.h
blockchain.o: block.h blockchain.h transaction.h merkel.h sha256.h sha256_utils.h cheater.h process.h config.h
transaction.o: block.h blockchain.h transaction.h merkel.h sha256.h sha256_utils.h cheater.h process.h config.h
merkel.o: block.h blockchain.h transaction.h merkel.h sha256.h sha256_utils.h cheater.h process.h config.h
sha256.o: block.h blockchain.h transaction.h merkel.h sha256.h sha256_utils.h cheater.h process.h config.h
sha256_utils.o: block.h blockchain.h transaction.h merkel.h sha256.h sha256_utils.h cheater.h process.h config.h
cheater.o: block.h blockchain.h transaction.h merkel.h sha256.h sha256_utils.h cheater.h cheater.h process.h process.h config.h
process.o: block.h blockchain.h transaction.h merkel.h sha256.h sha256_utils.h cheater.h cheater.h process.h process.h config.h
