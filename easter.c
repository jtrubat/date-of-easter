/*
    Easter. Displays the date of Easter.
    Copyright (C) 2016 Jordi Trubat.

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
#include <ctype.h>
#include <time.h>
#include <getopt.h>
#include <string.h>

#define NAME "easter"
#define VERSION "1.2.0"
#define AUTHOR "Jordi Trubat"
#define MAIL "jtrubat@uoc.edu"
#define EASTER_MIN_YEAR 1
#define EASTER_MAX_YEAR 9999
#define EASTER_GREGORIAN_YEAR 1583
#define EASTER_JULIAN_MIN_YEAR 1	//326?
#define EASTER_JULIAN_MAX_YEAR 1923
#define EASTER_GREGORIAN_MIN_YEAR 1583
#define EASTER_GREGORIAN_MAX_YEAR 4099
#define EASTER_ORTHODOX_MIN_YEAR 1583
#define EASTER_ORTHODOX_MAX_YEAR 4099
#define TRUE 1
#define FALSE 0

/* headers */
static void version (FILE *, int);
static void usage (FILE *, int);
static void help (FILE *, int);
void compute_easter (int, int, int *, int *);
void easterg (int, int *, int *);
void easterj (int, int *, int *);
void eastero (int, int *, int *);
void print_easter (int, int, int, int, int, int);
void print_date (int, int, int);
int isnum (char *);
void check_arg (char *, int, int, int *);
void check_year (int, int, int);


 /* main */
int
main (int argc, char *argv[])
{

  time_t t = time (NULL);
  struct tm *locp = localtime (&t);
  struct tm loc = *locp;
  int y;
  int west = FALSE;
  int orth = FALSE;
  int jul = FALSE;
  int header = FALSE;
  int a = 0;
  int b = 0;
  int intarg;

  /* cli options */
  int next_option;
  const char *const short_options = "hvywojH13A:B:";
  const struct option long_options[] = {
    {"help", 0, NULL, 'h'},
    {"version", 0, NULL, 'v'},
    {"western", 0, NULL, 'w'},
    {"orthodox", 0, NULL, 'o'},
    {"julian", 0, NULL, 'j'},
    {"header", 0, NULL, 'H'},
    {NULL, 2, &y, 'y'},
    {NULL, 0, NULL, '1'},
    {NULL, 0, NULL, '3'},
    {NULL, 1, NULL, 'A'},
    {NULL, 1, NULL, 'B'},
    {NULL, 0, NULL, 0}
  };

  do
    {
      next_option =
	getopt_long (argc, argv, short_options, long_options, NULL);
      switch (next_option)
	{
	case 'h':
	  help (stdout, 0);
	  break;
	case 'v':
	  version (stdout, 0);
	  break;
	case 'y':
	  break;
	case 'w':
	  west = TRUE;
	  break;
	case 'o':
	  orth = TRUE;
	  break;
	case 'j':
	  jul = TRUE;
	  break;
	case 'H':
	  header = TRUE;
	  break;
	case '1':
	  b = 0;
	  a = 0;
	  break;
	case '3':
	  b = 1;
	  a = 1;
	  break;
	case 'A':
	  if( (intarg=atoi(optarg)) > 0) {
	     a+=intarg;
	  } else {  
	     b+=-intarg;
	  }    
	  break;
	case 'B':
	  if( (intarg=atoi(optarg)) > 0) {
	     b+=intarg;
	  } else {  
	     a+=-intarg;
	  }    
	  break;
	case '?':
	  usage (stderr, 1);
	case -1:
	  break;
	default:
	  abort ();
	}
    }
  while (next_option != -1);



  if ((orth == FALSE) && (jul == FALSE))
    west = TRUE;

  if (header)
    {
      if (jul)
	printf ("Julian\t\t");
      if (west)
	printf ("Western\t\t");
      if (orth)
	printf ("Eastern");
      printf ("\n");
    }

  /* if no arguments */
  if (optind == argc)
    {

      /* get default year */
      y = 1900 + loc.tm_year;

      check_year (y, b, a);

      /* compute, print date of easter */
      print_easter (jul, west, orth, y, b, a);

    }
  else
    {

      /* read arguments */
      while (optind < argc)
	{

	  /* check argument */
	  check_arg (argv[optind++], b, a, &y);

	  /* compute, print date of easter */
	  print_easter (jul, west, orth, y, b, a);

	}
    }
  return EXIT_SUCCESS;
}


/* version */
static void
version (FILE * stream, int exit_code)
{
  fprintf (stream, "%s %s\n", NAME, VERSION);
  fprintf (stream,
	   "Copyright (C) 2016 Free Software Foundation, Inc. <http://fsf.org/>\n"
	   "This is free software with ABSOLUTELY NO WARRANTY.\n");
  fprintf (stream, "Written by %s.\n", AUTHOR);
  exit (exit_code);
}


/* usage */
static void
usage (FILE * stream, int exit_code)
{
  fprintf (stream,
	   "Usage: easter [general options] [-hjy] [year] ...\n"
	   "General options: [-31] [-A years] [-B years]\n");
  exit (exit_code);
}

/* help */
static void
help (FILE * stream, int exit_code)
{
  fprintf (stream, "Usage: %s options\n", NAME);
  fprintf (stream,
	   "  -y                 Display the date of Easter for the specified year.\n"
	   "                     Without argument the current year is implied.\n\n"
	   "  -3                 Display the previous, current and next date of Easter\n"
	   "                     surrounding the specified year.\n\n"
	   "  -1                 Display only date of Easter for the current year.\n"
	   "                     This is the default.\n\n"
	   "  -w, --western      Western Easter after gregorian calendar. For year 1583 on\n"
	   "                     this is the default.\n\n"
	   "  -o  --orthodox     Orthodox Easter after gregorian calendar.\n\n"
	   "  -j  --julian       Julian calendar. For year before 1583 this is the default.\n\n"
	   "  -H, --header       Display headers for Western, Eastern or Julian Easter.\n\n"
	   "  -A number          Years to add after. The specified number of years is added\n"
	   "                     to the end of the display. This is in addition to any date\n"
	   "                     range selected by the -y, -3, or -1 options. Negative\n"
	   "                     numbers are allowed, in which case the specified number of\n"
	   "                     years is subtracted. For example,  \"easter -y -B-2\"\n"
	   "                     produces the same result as \"easter -y -A2\": it shows\n"
	   "                     Easter date for the current year and the next two\n"
	   "                     following years.\n\n"
	   "  -B number          Years to add before. The specified number of years is\n"
	   "                     added to the beginning of the display. See -A for examples.\n\n"
	   "  -h  --help         Print this usage and exit.\n\n"
	   "  -v  --version      Print version information and exit\n\n"
	   "Report bugs to: <%s>\n", MAIL);

  exit (exit_code);
}

/*
   print date of easter
*/
void
print_easter (int j, int w, int o, int y, int b, int a)
{

  /* month and day of easter */
  int m, d;

  /* counter */
  int i;

  /* years range */
  for (i = -b; i < a + 1; i++)
    {

      /* julian easter */
      if (j)
	{
	  easterj (y + i, &m, &d);
	  print_date (y + i, m, d);
	}

      /* western easter */
      if (w)
	{
	  if (y + i < EASTER_GREGORIAN_YEAR)
	    {
	      easterj (y + i, &m, &d);
	    }
	  else
	    {
	      easterg (y + i, &m, &d);
	    }
	  print_date (y + i, m, d);
	}

      /* orthodox easter */
      if (o)
	{
	  if (y + i < EASTER_GREGORIAN_YEAR)
	    {
	      easterj (y + i, &m, &d);
	    }
	  else
	    {
	      eastero (y + i, &m, &d);
	    }
	  print_date (y + i, m, d);
	}
      printf ("\n");
    }
}

/*
   print date
*/
void
print_date (int y, int m, int d)
{
  char *months[] = { "March", "April", "May" };

  printf ("%-5s %2d %d\t", months[m - 3], d, y);
}


/*
 compute date of Easter (Gregorian Calendar), valid from 1583 on.
 in: 
 	year: 	year
 out:	
 	month:	month (3 or 4)
 	day:	day 
*/
void
easterg (int year, int *month, int *day)
{
  int a, b, c, d, e, f, g, h, i, k, l, m, n, p;

  a = year % 19;
  b = year / 100;
  c = year % 100;
  d = b / 4;
  e = b % 4;
  f = (b + 8) / 25;
  g = (b - f + 1) / 3;
  h = (19 * a + b - d - g + 15) % 30;
  i = c / 4;
  k = c % 4;
  l = (32 + 2 * e + 2 * i - h - k) % 7;
  m = (a + 11 * h + 22 * l) / 451;
  n = (h + l - 7 * m + 114) / 31;
  p = (h + l - 7 * m + 114) % 31;

  *month = n;
  *day = p + 1;
}

/*
 compute date of Easter (Julian Calendar)
 in: 
 	year: 	year
 out:	
 	month:	month (3 or 4)
 	day:	day 
*/
void
easterj (int year, int *month, int *day)
{
  int a, b, c, d, e, f, g;

  a = year % 4;
  b = year % 7;
  c = year % 19;
  d = (19 * c + 15) % 30;
  e = (2 * a + 4 * b - d + 34) % 7;
  f = (d + e + 114) / 31;
  g = (d + e + 114) % 31;

  *month = f;
  *day = g + 1;
}

/*
 compute date of Orthodox Easter (Julian Calendar), valid from 1583 on.
 in: 
 	year: 	year
 out:	
 	month:	month (4 or 5)
 	day:	day 
*/
void
eastero (int year, int *month, int *day)
{
  int a, b, c, d, e;

  a = year % 19;
  b = (19 * a + 15) % 30;
  c = (year + year / 4 + b) % 7;
  d = 10;
  if (year > 1600)
    d += year / 100 - 16 - (year / 100 - 16) / 4;
  e = b - c + d;

  *month = 3 + (e + 26) / 30;
  *day = 1 + (e + 27 + (e + 6) / 40) % 31;
}

/*
   check if string is numeric
 
   returns: non-zero if true, zero if not
*/
int
isnum (char *str)
{

  char c;
  int i = 0;

  while ((c = str[i++]) != '\0')
    if (!isdigit (c))
      return 0;
  return 1;
}

void
check_arg (char *str, int b, int a, int *y)
{
  if (!isnum (str))
    {
      fprintf (stderr, "%s: not a valid year %s\n", NAME, str);
      exit (1);
    }
  check_year (*y = strtoul (str, NULL, 10), a, b);
}


void
check_year (int y, int b, int a)
{
  int year;

  if (((year = y - b) < EASTER_MIN_YEAR)
      || ((year = y + a) > EASTER_MAX_YEAR))
    {
      fprintf (stderr, "%s: year `%d' not in range %d..%d\n",
	       NAME, year, EASTER_MIN_YEAR, EASTER_MAX_YEAR);
      exit (1);
    }
}
