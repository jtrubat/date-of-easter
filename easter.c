/*
 PROGRAM: easter. Displays the date of Easter.
 AUTHOR: Jordi Trubat.
 COPYRIGHT: Copyright (C) 2016 Free Software Foundation, Inc. <http://fsf.org/>
 This is free software with ABSOLUTELY NO WARRANTY.
*/

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "getopt.h"
#include "limits.h"

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
void print_version(FILE *,int);
void print_err0();
void print_usage(FILE * ,int );
void print_help(FILE * ,int );
 
 /* main */
int main(int argc, char *argv[])  {

    time_t t=time(NULL);
    struct tm *locp=localtime(&t);
    struct tm loc=*locp;
    char* months[]={"March","April"};    
    int year,month,day;
    int julian=FALSE;
    int after=0;
    int before=0;
    int i;
    
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

    /* no arguments */
    if(optind==argc)  {

        /* default year */
        year=1900+loc.tm_year;

        /* compute, print date of easter */
        for(i=-before;i<after+1;i++)  {
          if(year+i < 1) print_err0();
          if( (year+i>=1583)&&(!julian) )  {
             gregorian_easter(year+i,&month,&day);     
          } else {
             julian_easter(year+i,&month,&day);     
          }
          printf("%s %2d %d\n",months[month-3],day,year+i);
        }  
        
    } else {	
    
        /* read arguments */
        while(optind<argc) {
           if(!is_num_str(argv[optind])) print_usage(stderr,1); 
           year=atoi(argv[optind++]);

           /* compute, print date of easter */
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
    }	
    return EXIT_SUCCESS;
}


/*
 compute date of Easter (Gregorian Calendar), valid from 1583 on.
 in: 
 	y: 	year
 out:	
 	m:	month (3 or 4)
 	d:	day 
 returns:	 
 	0
*/
int gregorian_easter(int year, int *month, int *day)  {

    int a,b,c,d,e,f,g,h,i,k,l,m,n,p;

    a=year%19;
    b=year/100;
    c=year%100;
    d=b/4;
    e=b%4;
    f=(b+8)/25;
    g=(b-f+1)/3;
    h=(19*a+b-d-g+15)%30;
    i=c/4;
    k=c%4;
    l=(32+2*e+2*i-h-k)%7;
    m=(a+11*h+22*l)/451;
    n=(h+l-7*m+114)/31;
    p=(h+l-7*m+114)%31;
    
    *month=n;
    *day=p+1;
            
    return EXIT_SUCCESS;
}

/*
 compute date of Easter (Julian Calendar)
 in: 
 	y: 	year
 out:	
 	m:	month (3 or 4)
 	d:	day 
 returns:	 
 	0
*/
int julian_easter(int year, int *month, int *day)  {

    int a,b,c,d,e,f,g;

    a=year%4;
    b=year%7;
    c=year%19;
    d=(19*c+15)%30;
    e=(2*a+4*b-d+34)%7;
    f=(d+e+114)/31;
    g=(d+e+114)%31;
       
    *month=f;
    *day=g+1;
            
    return EXIT_SUCCESS;
}

int is_num_str(char *str)
{

  char c;
  int i=0;

  while( (c=str[i++])!='\0' )
    if(c<'0'|| c>'9') return 0;
  return 1;  
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

