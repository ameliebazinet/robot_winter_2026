MCU=atmega324pa

PROJECTNAME=libstatique

# Fichiers sources
# Utilisez le suffixe .cpp pour les fichiers C++
PRJSRC= $(wildcard *.cpp)

# Inclusions additionnels (ex: -I/path/to/mydir)
INC=-I.

# Niveau d'optimization
# Utilisez s (size opt), 1, 2, 3 ou 0 (off)
OPTLEVEL=s

# Programmer ID - Ne pas changer 
AVRDUDE_PROGRAMMERID=usbasp

####### variables #######

#compilateur utilise
CC=avr-gcc
#pour supprimer les fichiers lorsque l'on appel make clean
REMOVE=rm -f
# HEXFORMAT -- format pour les fichiers produient .hex
HEXFORMAT=ihex
# AVR-AR : crée la librairie statique à partir des .o
AR=avr-ar

####### Options de compilation #######

# Flags pour le compilateur en C
CFLAGS=-I. -I/usr/include/simavr -MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall

# Flag supplémentaire pour retirer le bogue de "array subscript 0 is outside 
# array bounds" sur avr-gcc v12
GCCVERSION := $(shell expr `$(CC) -dumpversion | cut -f1 -d.` \>= 12)
ifeq "$(GCCVERSION)" "1"
    CFLAGS += --param=min-pagesize=0
endif

# Flags pour le compilateur en C++
CXXFLAGS=-fno-exceptions

####### Definition de tout les fichiers objets #######

# Cette fonction permet de differencier les fichiers .c
# des fichiers .cpp
# Fichier C
CFILES=$(filter %.c, $(PRJSRC))
# Fichier C++
CPPFILES=$(filter %.cpp, $(PRJSRC))

# Liste de tout les fichiers objet que nous devons creer
OBJDEPS=$(CFILES:.c=.o) $(CPPFILES:.cpp=.o)
	
####### Creation des commandes du Makefile ####### 

# Creation des cibles Phony (Phony Target)
# En plus de la commande make qui permet de compiler
# votre projet, vous pouvez utilisez les commandes
# make all, make install et make clean
.PHONY: all clean

# Make all permet simplement de compiler le projet
#
all: $(PROJECTNAME).a

# Production des fichiers object
# De C a objet
%.o: %.c
	$(CC) $(CFLAGS) -c $<
# De C++ a objet
%.o: %.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $<

# Verification des dependances (header dependencies)
-include *.d

# De .o à .a

# Make clean permet d'effacer tout les fichiers generes
# lors de la compilation
clean:
	$(REMOVE) $(TRG) $(TRG).map $(OBJDEPS) $(HEXTRG) *.d
