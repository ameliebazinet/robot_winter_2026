########       AVR Project Makefile (lib)      ########

MCU=atmega324pa
PROJECTNAME=libstatique

# Fichiers sources
PRJSRC= $(wildcard *.cpp)

# Inclusions additionnelles
INC=-I.

# Niveau d'optimisation
OPTLEVEL=s

# Programmer ID
AVRDUDE_PROGRAMMERID=usbasp

####### variables #######

CC=avr-gcc
REMOVE=rm -f
HEXFORMAT=ihex
AR=avr-ar

####### Flags #######

# Flags pour le compilateur en C
CFLAGS=-MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall

# Flag supplémentaire pour retirer le bogue de "array subscript 0 is outside 
# array bounds" sur avr-gcc v12
GCCVERSION := $(shell expr `$(CC) -dumpversion | cut -f1 -d.` \>= 12)
ifeq "$(GCCVERSION)" "1"
    CFLAGS += --param=min-pagesize=0
endif

# Flags pour le compilateur en C++
CXXFLAGS=-fno-exceptions

####### Fichiers objets #######

CFILES=$(filter %.c, $(PRJSRC))
CPPFILES=$(filter %.cpp, $(PRJSRC))
OBJDEPS=$(CFILES:.c=.o) $(CPPFILES:.cpp=.o)
	
####### Creation des commandes du Makefile ####### 

.PHONY: all clean

all: $(PROJECTNAME).a

# De C a objet
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# De C++ a objet
%.o: %.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $<

# De .o à .a
$(PROJECTNAME).a: $(OBJDEPS)
	$(AR) rcs $@ $^

# Verification des dependances
-include *.d

clean:
	$(REMOVE) $(PROJECTNAME).a $(OBJDEPS) *.d