/*
 PROGRAM: easter. Displays the date of Easter.
 AUTHOR: Jordi Trubat.
 COPYRIGHT: Copyright (C) 2016 Free Software Foundation, Inc. <http://fsf.org/>
 This is free software with ABSOLUTELY NO WARRANTY.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include <limits.h>

#define NAME "easter"
#define VERSION "1.0.3"
#define AUTHOR "Jordi Trubat"
#define MAIL "jtrubat@uoc.edu"
#define TRUE 1
#define FALSE 0

/* headers */
int gregorian_easter(int, int *, int *);
int julian_easter(int, int *, int *);
int is_num_str(char *);
void print_easter(int, int, int, int);
void print_version(FILE *,int);
void print_err0();
void print_usage(FILE * ,int );
void print_help(FILE * ,int );
 
