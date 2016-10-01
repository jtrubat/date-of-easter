#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "getopt.h"

#define NAME "easter"
#define VERSION "1.0.0"
#define AUTHOR "Jordi Trubat"
#define MAIL "jtrubat@uoc.edu"

/* headers */
int compute_easter(int, int *, int *);
void print_version(FILE *,int);
void print_usage(FILE * ,int );
 
 /* main */
int main(int argc, char *argv[])  {

    time_t t=time(NULL);
    struct tm *locp=localtime(&t);
    struct tm loc=*locp;
    char* months[]={"March","April"};    
    int year,month,day;
    int after=0;
    int before=0;
    int i;
    
    /* cli options */
    int next_option;
    const char* const short_options="hvy13A:B:";
    const struct option long_options[]= {
      {"help",0,NULL,'h'},
      {"version",0,NULL,'v'},
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
        print_usage(stdout,0);
        break;
     case 'v':
        print_version(stdout,0);
        break;
     case 'y':
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
          compute_easter(year+i,&month,&day);     
          printf("%s %2d %d\n",months[month-3],day,year+i);
        }  
        
    } else {	
    
        /* read arguments */
        while(optind<argc) {
           year=atoi(argv[optind++]);

           /* compute, print date of easter */
           for(i=-before;i<after+1;i++)  {
              compute_easter(year+i,&month,&day);     
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
int compute_easter(int year, int *month, int *day)  {

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
 print version
*/
void print_version(FILE *stream,int exit_code)
{
  fprintf(stream,"%s %s\n",NAME,VERSION);
  fprintf(stream, "Written by %s.\n",AUTHOR); 
  exit(exit_code);  
}

/*
 print usage
*/
void print_usage(FILE *stream,int exit_code)
{
  fprintf(stream,"Usage: %s options\n",NAME);
  fprintf(stream,
    "  -y                 Display the date of Easter for the specified year.\n"
    "                     Without argument the current year is implied.\n\n"
    "  -3                 Display the previous, current and next date of Easter\n"
    "                     surrounding the specified year.\n\n"
    "  -1                 Display only date of Easter for the current year.\n"
    "                     This is the default.\n\n"
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

