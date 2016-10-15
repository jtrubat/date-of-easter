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

#include "easter.h"
 
 /* main */
int main(int argc, char *argv[])  {

    time_t t=time(NULL);
    struct tm *locp=localtime(&t);
    struct tm loc=*locp;
    int year;
    int julian=FALSE;
    int after=0;
    int before=0;
    
    /* cli options */
    int next_option;
    const char* const short_options="hvyj13A:B:";
    const struct option long_options[]= {
      {"help",0,NULL,'h'},
      {"version",0,NULL,'v'},
      {"julian",0,NULL,'j'},
      {NULL,2,&year,'y'},
      {NULL,0,NULL,'1'},
      {NULL,0,NULL,'3'},
      {NULL,1,NULL,'A'},
      {NULL,1,NULL,'B'},
      {NULL,0,NULL,0}
      };

    do {
        next_option=getopt_long(argc,argv,short_options,long_options,NULL);
        switch(next_option)  {
     case 'h':
        print_help(stdout,0);
        break;
     case 'v':
        print_version(stdout,0);
        break;
     case 'y':
        break;   
     case 'j':
        julian=TRUE;
        break;   
     case '1':
        before=0;
        after=0;        
        break;   
     case '3':
        before=1;
        after=1;
        break;           
     case 'A':
        after+=atoi(optarg);
        break;   
     case 'B':
        before+=atoi(optarg);
        break;   
     case '?':        
        print_usage(stderr,1);
     case -1:
        break;  
     default:
        abort();
        }
    } while(next_option!=-1);

    /* if no arguments */
    if(optind==argc)  {

        /* get default year */
        year=1900+loc.tm_year;
        
        /* compute, print date of easter */
        print_easter(year, before, after, julian);

    } else {	
    
        /* read arguments */
        while(optind<argc) {
        
           /* check arguments */
           if(!is_num_str(argv[optind])) print_usage(stderr,1); 
           
           /* for every year */
           year=atoi(argv[optind++]);

           /* compute, print date of easter */
           print_easter(year, before, after, julian);
        }    
    }	
    return EXIT_SUCCESS;
}

/*
   print date of easter
*/
void print_easter(int year, int before, int after, int julian)
{

    char* months[]={"March","April"};    
    int month,day;
    int i;

   for(i=-before;i<after+1;i++)  {
      if(year+i < 1) print_err0();
      if( (year+i>=1583)&&(!julian) )  {
          gregorian_easter(year+i,&month,&day);     
      } else {
          julian_easter(year+i,&month,&day);     
      }
      printf("%s %2d %d\n",months[month-3],day,year+i);
   }
}

/*
   print version
*/
void print_version(FILE *stream,int exit_code)
{
  fprintf(stream,"%s %s\n",NAME,VERSION);
  fprintf(stream,
  "Copyright (C) 2016 Free Software Foundation, Inc. <http://fsf.org/>\n"
  "This is free software with ABSOLUTELY NO WARRANTY.\n");
  fprintf(stream, "Written by %s.\n",AUTHOR); 
  exit(exit_code);  
}

/*
   print err0
*/
void print_err0()
{
  fprintf(stderr,"%s: year not in range 1..%d\n",NAME,INT_MAX);
  exit(1);    
}


/*
   print usage
*/
void print_usage(FILE *stream,int exit_code)
{
  fprintf(stream,
    "Usage: easter [general options] [-hjy] [year] ...\n"
    "General options: [-31] [-A years] [-B years]\n");
  exit(exit_code);    
}

/*
   print help
*/

void print_help(FILE *stream,int exit_code)
{
  fprintf(stream,"Usage: %s options\n",NAME);
  fprintf(stream,
    "  -y                 Display the date of Easter for the specified year.\n"
    "                     Without argument the current year is implied.\n\n"
    "  -3                 Display the previous, current and next date of Easter\n"
    "                     surrounding the specified year.\n\n"
    "  -1                 Display only date of Easter for the current year.\n"
    "                     This is the default.\n\n"
    "  -j  --julian       Force Julian calendar.\n\n"
    "  -A number          Years to add after. The specified number of years is\n"
    "                     added to the end of the display. This is in addition\n"
    "                     to any date range selected by the -y, -3, or -1 options.\n\n"
    "  -B number          Years to add before. The specified number of years is\n"
    "                     added to the beginning of the display. This is in addition\n"
    "                     to any date range selected by the -y, -3, or -1 options.\n\n"
    "  -h  --help         Print this usage and exit.\n\n"
    "  -v  --version      Print version information and exit\n");
  exit(exit_code);  
}

