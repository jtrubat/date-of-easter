#include "easter.h"

void print_usage(FILE *stream,int exit_code)
{
  fprintf(stream,"Usage: %s options\n",PROGRAM_NAME);
  fprintf(stream,
    "  -h  --help         Print this usage and exit.\n\n"
    "  -y                 Display the date of Easter for the specified year.\n"
    "                     Without argument the current year is implied.\n\n"
    "  -3                 Display the previous, current and next date of Easter\n"
    "                     surrounding the specified year.\n\n"
    "  -1                 Display only date of Easter for the current year.\n"
    "                     This is the default.\n\n"
    "  -A number          Years to add after. The specified number of years is\n"
    "                     added to the end of the display. This is in addition\n"
    "                     to any date range selected by the -y, -3, or -1 options.\n"
    "                     For example, “easter -y -B2 -A2” shows the date of Easter\n"
    "                     from two years before the current year to two years after\n"
    "                     the current year.\n\n"
    "  -v  --version      Print version information and exit\n");
  exit(exit_code);  
}


