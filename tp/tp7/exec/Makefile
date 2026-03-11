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