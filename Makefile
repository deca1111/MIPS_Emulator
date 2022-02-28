## Change this variable
MYNAME=VALETTE_MONTOYA
# and perhaps this one
SRCDOC=ReadMe.txt
# testfiles are in TESTDIR and IGNORE = list of files to ignore when taring
TESTDIR = dossier_tests/
IGNORE = old_generate.c.old
## Do not change below please
BIN = emul-mips
PREFIX=MIPS3
CC = gcc
FLAGS = -Wall
C_FILES = $(wildcard *.c)
OBJ_FILES = $(C_FILES:.c=.o)

OBJECTS = main.o traduction.o data.o memoire.o fonctions_outils.o registres.o execution.o

OPTIONS = -Wall -o


all : binary

binary: $(OBJECTS)
	gcc $(OBJECTS) -o $(BIN) -lm

main.o : main.c
	gcc -c main.c $(OPTIONS) main.o

traduction.o : traduction.c
	gcc -c traduction.c $(OPTIONS) traduction.o

memoire.o : memoire.c
	gcc -c memoire.c $(OPTIONS) memoire.o

fonctions_outils.o : fonctions_outils.c
	gcc -c fonctions_outils.c $(OPTIONS) fonctions_outils.o

data.o : data.c
	gcc -c data.c $(OPTIONS) data.o

registres.o : registres.c
	gcc -c registres.c $(OPTIONS) registres.o

execution.o : execution.c
	gcc -c execution.c $(OPTIONS) execution.o

clean:
	rm -f *.o *~ $(BIN) *.hex *.s

# a useful command to generate a pdf from a .md documentation file
doc : $(SRCDOC)
	pandoc -f markdown -t pdf  $(SRCDOC) -o $(basename $(SRCDOC)).pdf


# A useful command to deliver your project while keeping me sane
tar: clean
	dir=$$(basename $$PWD) && echo "compressing $(dir)" && cd .. && \
	tar cvfz "$(PREFIX)-$(MYNAME).tgz" \
	--transform="s,^$$dir,$(PREFIX)-$(MYNAME)," \
	--exclude="$(IGNORE)" "$$dir" --verbose --show-transformed-names

