/*
 PROGRAM: easter. Displays the date of Easter.
 AUTHOR: Jordi Trubat.
 COPYRIGHT: Copyright (C) 2016 Free Software Foundation, Inc. <http://fsf.org/>
 This is free software with ABSOLUTELY NO WARRANTY.
*/

#include "easter.h"
 
/*
   check if string is numeric
 
   returns: non-zero if true, zero if not
*/
int is_num_str(char *str)
{

  char c;
  int i=0;

  while( (c=str[i++])!='\0' )
    if(c<'0'|| c>'9') return 0;
  return 1;  
}

