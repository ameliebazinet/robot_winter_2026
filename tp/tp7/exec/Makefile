########       AVR Project Makefile (exec)      ########

MCU=atmega324pa
PROJECTNAME=main

# Fichier source exec
PRJSRC=main.cpp

# Librairie
LIBDIR=../lib
LIBS=$(LIBDIR)/libstatique.a

# Fichiers sources dans lib/
LIBCSRC=$(wildcard $(LIBDIR)/*.c)
LIBCPPSRC=$(wildcard $(LIBDIR)/*.cpp)

# Inclusions : headers de la lib
INC= -I. -I$(LIBDIR)

# Niveau d'optimisation
OPTLEVEL=s

# Programmer ID
AVRDUDE_PROGRAMMERID=usbasp

####### Variables #######

CC=avr-gcc
AR=avr-ar
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

####### Fichiers objets #######

MAINOBJ=$(PRJSRC:.cpp=.o)
LIBCOBJ=$(LIBCSRC:.c=.o)
LIBCPPOBJ=$(LIBCPPSRC:.cpp=.o)
LIBOBJ=$(LIBCOBJ) $(LIBCPPOBJ)

####### Commandes #######

.PHONY: all debug install clean

all: $(LIBS) $(TRG) $(HEXROMTRG)

debug: CFLAGS += -DDEBUG

debug: all

# Cree la librairie statique directement depuis exec/
$(LIBS): $(LIBOBJ)
	$(AR) rcs $(LIBS) $(LIBOBJ)

# Lie main.o avec la librairie statique
$(TRG): $(MAINOBJ) $(LIBS)
	$(CC) $(LDFLAGS) -o $@ $^ -lm

# Compilation des fichiers .cpp dans exec/
%.o: %.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

# Compilation des fichiers .cpp dans lib/
$(LIBDIR)/%.o: $(LIBDIR)/%.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

%.hex: %.elf 
	$(OBJCOPY) -j .text -j .data -O $(HEXFORMAT) $< $@

install: $(HEXROMTRG)
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMERID) \
	-p $(MCU) -P usb -B 10 -e -U flash:w:$(HEXROMTRG)
clean:
	$(REMOVE) *.o *.d $(TRG) $(HEXROMTRG) *.map
	$(REMOVE) $(LIBS) $(LIBDIR)/*.o $(LIBDIR)/*.d

-include *.d
-include $(LIBDIR)/*.d

#####                    EOF                   #####