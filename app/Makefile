########       AVR Project Makefile (exec)      ########
# Auteurs : Amélie Bazinet (2447346), Ayhem Cheikh (2440359), Vincent Dufresne (2455479) et Félix Tétreault (2464852)
# Description : Makefile pour la compilation de l'exécutable principal du projet de robot suiveur de ligne.
# Ce Makefile compile le fichier source principal, lie la bibliothèque statique et génère un fichier .hex pour être installé sur la carte.

MCU=atmega324pa
PROJECTNAME=main

# Fichier source exec
PRJSRC=main.cpp modes/execution.cpp lecture/lecture.cpp

# Librairie
LIBDIR=../lib
LIBS=$(LIBDIR)/libstatique.a


# Inclusions : headers de la lib
INC= -I. -I$(LIBDIR)

# Niveau d'optimisation
OPTLEVEL=s

# Programmer ID
AVRDUDE_PROGRAMMERID=usbasp

####### Variables #######

CC=avr-gcc
OBJCOPY=avr-objcopy
AVRDUDE=avrdude
REMOVE=rm -f
HEXFORMAT=ihex

####### Flags #######

CFLAGS= $(INC) -MMD -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall
CXXFLAGS=-fno-exceptions
LDFLAGS=-Wl,-Map,$(TRG).map -mmcu=$(MCU)

####### Cible (Target) #######

TRG=$(PROJECTNAME).elf
HEXROMTRG=$(PROJECTNAME).hex

####### Objet de l'executable #######

MAINOBJ=$(PRJSRC:.cpp=.o)

####### Commandes #######

.PHONY: all debug install clean

all: $(LIBS) $(TRG) $(HEXROMTRG)

debug: CFLAGS += -DDEBUG
debug: all

# Lie main.o avec la librairie statique
$(TRG): $(MAINOBJ) $(LIBS)
	$(CC) $(LDFLAGS) -o $@ $^ -lm

# Compilation des fichiers .cpp dans exec/
%.o: %.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

# Conversion de l'executable en format hex
%.hex: %.elf 
	$(OBJCOPY) -j .text -j .data -O $(HEXFORMAT) $< $@

# Installation du programme sur la carte
install: $(HEXROMTRG)
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMERID) \
	-p $(MCU) -P usb -B 10 -e -U flash:w:$(HEXROMTRG)

# Nettoyage des .o, des dépendances et des executables
clean:
	$(REMOVE) *.o *.d $(TRG) $(HEXROMTRG) *.map

-include *.d

#####                    EOF                   #####