#    Makefile for easter
#
#    This file is part of Easter.
#
#    Easter is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    Easter is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
#    
#    The author can be contacted at <jtrubat@uoc.edu>
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
#OBJECTS=$(EXEC).o compute.o utils.o error.o
OBJECTS=easter.o
		
# Executable
$(EXEC):	$(INCLUDES) $(OBJECTS)
		$(CC) $(CFLAGS) $(OBJECTS) $(SLIBS) -o $@
        
#main.o:	main.c
#		$(CC) $(CFLAGS) -c main.c
		

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

# make uninstall
.PHONY: uninstall
uninstall:
		rm $(INSTALLDIR)/$(EXEC)
		rm $(MANPAGEDIR)/$(EXEC).1.gz


