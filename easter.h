/*
    This file is part of Easter.

    Easter is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Easter is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    
    The author can be contacted at <jtrubat@uoc.edu>
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include <limits.h>

#define NAME "easter"
#define VERSION "1.0.4"
#define AUTHOR "Jordi Trubat"
#define MAIL "jtrubat@uoc.edu"
#define TRUE 1
#define FALSE 0

/* headers */
void gregorian_easter(int, int *, int *);
void julian_easter(int, int *, int *);
int is_num_str(char *);
void print_easter(int, int, int, int);
void print_version(FILE *,int);
void print_err0();
void print_usage(FILE * ,int );
void print_help(FILE * ,int );
 
