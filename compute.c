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
 compute date of Easter (Gregorian Calendar), valid from 1583 on.
 in: 
 	y: 	year
 out:	
 	m:	month (3 or 4)
 	d:	day 
*/
void gregorian_easter(int year, int *month, int *day)
{
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
}

/*
 compute date of Easter (Julian Calendar)
 in: 
 	y: 	year
 out:	
 	m:	month (3 or 4)
 	d:	day 
*/
void julian_easter(int year, int *month, int *day)
{
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
}

