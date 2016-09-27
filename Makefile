#
# Makefile for easter
#

EXEC=easter
CC=gcc
CFLAGS=-Wall
LEX=
YACC=
INCLUDES=
SLIBS=
LEXFILE=
YACCFILE=

# Object files
OBJECTS=$(EXEC).o cal_easter.o help.o

# Executable
$(EXEC):	$(INCLUDES) $(OBJECTS)
		$(CC) $(CFLAGS) $(OBJECTS) $(SLIBS) -o $@
        
$(EXE).o:	$(EXEC).c
		$(CC) $(CFLAGS) -c $(EXEC).c
		
cal_easter.o:	cal_easter.c
		$(CC) $(CFLAGS) -c cal_easter.c

help.o:		help.c
		$(CC) $(CFLAGS) -c help.c
		
# Clean object files
.PHONY: clean
clean:
		rm -f *.o

# make all
.PHONY: all
all:		$(EXEC) clean	


