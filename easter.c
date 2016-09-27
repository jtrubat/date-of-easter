#include "easter.h"
 
int main(int argc, char *argv[])  {

    time_t t=time(NULL);
    struct tm *locp=localtime(&t);
    struct tm loc=*locp;
    char* months[]={"March","April"};    
    int month,day;
    int after=0;
    int before=0;
    int i;
    
    /* default year */
    int year=1900+loc.tm_year;

    /* command line options */
    int next_option;
    const char* const short_options="hqvy13A:B:";
    const struct option long_options[]= {
      {"help",0,NULL,'h'},
      {"quiet",0,NULL,'q'},
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
     case 'q':
        /*version=FALSE;*/
        break;
     case 'v':
        /*version=TRUE;
        quit=TRUE;*/
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
     case -1:
        break;  
     default:
        return EXIT_FAILURE;
        }
    } while(next_option!=-1);

    /* year as parameter */	
    if(optind<argc) {
        year=atoi(argv[optind]);
    }
    
    /* compute and print date of easter */
    for(i=-before;i<after+1;i++)  {
      cal_easter(year+i,&month,&day);     
      printf("%s %2d %d\n",months[month-3],day,year+i);
    }
	
    return EXIT_SUCCESS;
}

