########       AVR Project Makefile       ########
#####                                        #####
#####      Makefile produit et ecrit par     #####
#####   Simon Barrette & Jerome Collin pour  #####
#####           INF1900 - 2016               #####
##################################################

MCU=atmega324pa
PROJECTNAME=tp7

# Fichier source present seulement dans exec/
PRJSRC=main.cpp

# Dossier de librairie
LIBDIR=../lib
LIBS=$(LIBDIR)/libstatique.a

# Tous les fichiers sources dans lib/
LIBCSRC=$(wildcard $(LIBDIR)/*.c)
LIBCPPSRC=$(wildcard $(LIBDIR)/*.cpp)

# Inclusions : headers de la lib
INC=-I$(LIBDIR)

# Niveau d'optimization
OPTLEVEL=s

# Programmer ID
AVRDUDE_PROGRAMMERID=usbasp

####### variables #######

CC=avr-gcc
AR=avr-ar
OBJCOPY=avr-objcopy
AVRDUDE=avrdude
REMOVE=rm -f
HEXFORMAT=ihex

####### Options de compilation #######

CFLAGS=-I. $(INC) -MMD -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall

GCCVERSION := $(shell expr `$(CC) -dumpversion | cut -f1 -d.` \>= 12)
ifeq "$(GCCVERSION)" "1"
    CFLAGS += --param=min-pagesize=0
endif

CXXFLAGS=-fno-exceptions
LDFLAGS=-Wl,-Map,$(TRG).map -mmcu=$(MCU)

####### Cible (Target) #######

TRG=$(PROJECTNAME).elf
HEXROMTRG=$(PROJECTNAME).hex
HEXTRG=$(HEXROMTRG) $(PROJECTNAME).ee.hex

####### Fichiers objets #######

MAINOBJ=$(PRJSRC:.cpp=.o)
LIBCOBJ=$(LIBCSRC:.c=.o)
LIBCPPOBJ=$(LIBCPPSRC:.cpp=.o)

OBJDEPS=$(MAINOBJ)
LIBOBJ=$(LIBCOBJ) $(LIBCPPOBJ)

####### Commandes #######

.PHONY: all debug install clean lib

all: $(LIBS) $(TRG) $(HEXROMTRG)

debug: CFLAGS += -DDEBUG
debug: $(LIBS) $(TRG) $(HEXROMTRG)

# Cree la librairie statique directement depuis exec/
$(LIBS): $(LIBOBJ)
	$(AR) rcs $(LIBS) $(LIBOBJ)

# Lie main.o avec la librairie statique
$(TRG): $(OBJDEPS) $(LIBS)
	$(CC) $(LDFLAGS) -o $(TRG) $(OBJDEPS) $(LIBS) -lm

# Compilation des fichiers .c dans exec/
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation des fichiers .cpp dans exec/
%.o: %.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

# Compilation des fichiers .c dans lib/
$(LIBDIR)/%.o: $(LIBDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation des fichiers .cpp dans lib/
$(LIBDIR)/%.o: $(LIBDIR)/%.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

-include *.d
-include $(LIBDIR)/*.d

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O $(HEXFORMAT) $< $@

install: $(HEXROMTRG)
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMERID) \
	-p $(MCU) -P usb -B 10 -e -U flash:w:$(HEXROMTRG)
clean:
	$(REMOVE) $(TRG) $(TRG).map $(OBJDEPS) $(HEXTRG) *.d
	$(REMOVE) $(LIBOBJ) $(LIBS) $(LIBDIR)/*.d

#####                    EOF                   #####




# MCU=atmega324pa

# PROJECTNAME=libstatique

# # Fichiers sources
# # Utilisez le suffixe .cpp pour les fichiers C++
# PRJSRC= $(wildcard *.cpp)

# # Inclusions additionnels (ex: -I/path/to/mydir)
# INC=-I.

# # Niveau d'optimization
# # Utilisez s (size opt), 1, 2, 3 ou 0 (off)
# OPTLEVEL=s

# # Programmer ID - Ne pas changer 
# AVRDUDE_PROGRAMMERID=usbasp

# ####### variables #######

# #compilateur utilise
# CC=avr-gcc
# #pour supprimer les fichiers lorsque l'on appel make clean
# REMOVE=rm -f
# # HEXFORMAT -- format pour les fichiers produient .hex
# HEXFORMAT=ihex
# # AVR-AR : crée la librairie statique à partir des .o
# AR=avr-ar

# ####### Options de compilation #######

# # Flags pour le compilateur en C
# CFLAGS=-I. -I/usr/include/simavr -MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
# 	-std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall

# # Flag supplémentaire pour retirer le bogue de "array subscript 0 is outside 
# # array bounds" sur avr-gcc v12
# GCCVERSION := $(shell expr `$(CC) -dumpversion | cut -f1 -d.` \>= 12)
# ifeq "$(GCCVERSION)" "1"
#     CFLAGS += --param=min-pagesize=0
# endif

# # Flags pour le compilateur en C++
# CXXFLAGS=-fno-exceptions

# ####### Definition de tout les fichiers objets #######

# # Cette fonction permet de differencier les fichiers .c
# # des fichiers .cpp
# # Fichier C
# CFILES=$(filter %.c, $(PRJSRC))
# # Fichier C++
# CPPFILES=$(filter %.cpp, $(PRJSRC))

# # Liste de tout les fichiers objet que nous devons creer
# OBJDEPS=$(CFILES:.c=.o) $(CPPFILES:.cpp=.o)
	
# ####### Creation des commandes du Makefile ####### 

# # Creation des cibles Phony (Phony Target)
# # En plus de la commande make qui permet de compiler
# # votre projet, vous pouvez utilisez les commandes
# # make all, make install et make clean
# .PHONY: all clean

# # Make all permet simplement de compiler le projet
# #
# all: $(PROJECTNAME).a

# # Production des fichiers object
# # De C a objet
# %.o: %.c
# 	$(CC) $(CFLAGS) -c $<
# # De C++ a objet
# %.o: %.cpp
# 	$(CC) $(CFLAGS) $(CXXFLAGS) -c $<

# # Verification des dependances (header dependencies)
# -include *.d

# # De .o à .a
# $(PROJECTNAME).a: $(OBJDEPS)
# 	$(AR) -c -r -s $@ $(OBJDEPS)

# # Make clean permet d'effacer tout les fichiers generes
# # lors de la compilation
# clean:
# 	$(REMOVE) $(TRG) $(TRG).map $(OBJDEPS) $(HEXTRG) *.d