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

