#
# Makefile for easter
#

EXEC=easter
INSTALLDIR=/usr/local/bin
MANPAGEDIR=/usr/local/man/man1
CC=gcc
CFLAGS=-Wall
LEX=
YACC=
INCLUDES=
SLIBS=
LEXFILE=
YACCFILE=

# Object files
OBJECTS=$(EXEC).o compute.o utils.o

# Executable
$(EXEC):	$(INCLUDES) $(OBJECTS)
		$(CC) $(CFLAGS) $(OBJECTS) $(SLIBS) -o $@
        
$(EXE).o:	$(EXEC).c
		$(CC) $(CFLAGS) -c $(EXEC).c
		
compute.o:	compute.c
		$(CC) $(CFLAGS) -c compute.c

utils.o:	utils.c
		$(CC) $(CFLAGS) -c utils.c

# Clean object files
.PHONY: clean
clean:
		rm -f *.o

# make all
.PHONY: all
all:
		$(EXEC) clean	

# make install
.PHONY: install
install:
		cp --remove-destination $(EXEC) $(INSTALLDIR)
		cp --remove-destination $(EXEC).1 $(MANPAGEDIR)/$(EXEC).1
		gzip -f $(MANPAGEDIR)/$(EXEC).1


