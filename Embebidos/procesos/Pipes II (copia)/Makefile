#Archivo Makefile simple
PRYECTO=pipe_II
DESTDIR=/usr/local/bin
CFLAGS=-Wall
LFLAGS=-lm
CC=gcc
OBJS=$(SRCC:.C=.o)
SRCC =$(wildcard *.c)

all: $(PRYECTO)

%.o: %.c
	$(CC) -c $< $(FLAGS)


$(PRYECTO): $(OBJS)
	$(CC) $^ -o $@ $(LFLAGS)

ejecutar: $(PRYECTO)
	./$(PRYECTO)

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
