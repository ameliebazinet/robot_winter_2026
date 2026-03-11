########       AVR Project Makefile       ########
#####                                        #####
#####      Makefile produit et ecrit par     #####
#####   Simon Barrette & Jerome Collin pour  #####
#####           INF1900 - 2016               #####
#####                                        #####
#####         Inspire de Pat Deegan -        #####
#####  Psychogenic Inc (www.psychogenic.com) #####
##################################################

MCU=atmega324pa
PROJECTNAME=Communicaton
PRJSRC=main.cpp Communication.cpp
INC=
LIBS=
OPTLEVEL=s
AVRDUDE_PROGRAMMERID=usbasp

####### variables #######

CC=avr-gcc
OBJCOPY=avr-objcopy
AVRDUDE=avrdude
REMOVE=rm -f
HEXFORMAT=ihex

####### Options de compilation #######

CFLAGS=-I. -I/usr/include/simavr -MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
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

####### Definition de tout les fichiers objets #######

CFILES=$(filter %.c, $(PRJSRC))
CPPFILES=$(filter %.cpp, $(PRJSRC))

OBJDEPS=$(CFILES:.c=.o) \
	$(CPPFILES:.cpp=.o)

####### Creation des commandes du Makefile ####### 

.PHONY: all install clean debug

all: $(TRG) $(HEXROMTRG)

# Cible debug : passe -DDEBUG au compilateur uniquement (pas au linker)
debug: CFLAGS += -DDEBUG
debug: all

$(TRG): $(OBJDEPS)
	$(CC) $(LDFLAGS) -o $(TRG) $(OBJDEPS) -lm $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.o: %.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $<

-include *.d

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O $(HEXFORMAT) $< $@

install: $(HEXROMTRG)
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMERID) -p $(MCU) -P usb -e -U flash:w:$(HEXROMTRG)

clean:
	$(REMOVE) $(TRG) $(TRG).map $(OBJDEPS) $(HEXTRG) *.d

#####                    EOF                   #####
