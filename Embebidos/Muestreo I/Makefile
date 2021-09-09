#Archivo Makefile simple
PRYECTO=muestreo
DESTDIR=/usr/local/bin
CFLAGS=-Wall
LFLAGS=-lm
CC=gcc
OBJS=$(SRCC:.C=.o)
SRCC =$(wildcard *.c)

all: $(PRYECTO)

%.o: %.c
	$(CC) -c $< $(FLAGS)

# muestreo.o: muestreo.c
# 	$(CC) -c muestreo.c $(CFLAGS)
	
# procesamiento.o: procesamiento.c
# 	$(CC) -c procesamiento.c $(CFLAGS)

# archivos.o: archivos.c
# 	$(CC) -c archivos.c $(CFLAGS)


$(PRYECTO): $(OBJS)
	$(CC) $^ -o $@ $(LFLAGS)

# $(PRYECTO): muestreo.o procesamiento.o archivos.o 
# 	$(CC) muestreo.o procesamiento.o archivos.o -o $(PRYECTO) $(LFLAGS)

ejecutar: $(PRYECTO)
	./muestreo

.PHONY: clean install uninstall

install: all
	if [ ! -d $(DESTDIR) ]; then \
		sudo mkdir $(DESTDIR) ; \
	fi; \
	sudo cp $(PRYECTO) $(DESTDIR) 

uninstall: 
	sudo rm $(DESTDIR)/$(PRYECTO) 

clean:
	rm -f *.o $(PRYECTO) *.dat	
