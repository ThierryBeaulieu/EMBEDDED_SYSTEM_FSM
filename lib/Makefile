#Variables

#Compilateur
CC=avr-gcc
#Nom du fichier exécutable
EXEC=librobot.a
#Pour supprimer les fichiers lorsque l'on appel make clean
REMOVE=rm -f
#Aller trouver tous les fichers .cpp et les mettre dans une liste SOURCES
SOURCES=$(wildcard *.cpp)
#Convertit tous les fichers dans SOURCES en .o
OBJECTS=$(SOURCES:.cpp=.o)
# Nom du microcontroleur cible
# (exemple: 'at90s8515')
MCU=atmega324pa

# Niveau d'optimization
# Utilisez s (size opt), 1, 2, 3 ou 0 (off)
OPTLEVEL=s

# Flags pour le compilateur en C++
CXXFLAGS=-fno-exceptions  

CFLAGS=-I. -I/usr/include/simavr -MMD -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-std=c++14 -fpack-struct -fshort-enums             \
	-funsigned-bitfields -funsigned-char    \
	-Wall -DF_CPU=8000000UL

all: $(EXEC)

$(EXEC):$(OBJECTS)
	ar -crs $(EXEC) $(OBJECTS)

%.o:%.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c -o $@ $< 

# Verification des dependances (header dependencies)
-include *.d

#Permet de voir les fichier sources et objets utilisés pour la compilation
#Utile pour le déboguage
variables: 
	@echo "SOURCES = $(SOURCES)"
	@echo "OBJECTS = $(OBJECTS)"

clean:
	$(REMOVE) *.o
	$(REMOVE) *.a
	$(REMOVE) *.d