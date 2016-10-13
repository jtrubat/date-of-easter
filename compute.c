/*
 PROGRAM: easter. Displays the date of Easter.
 AUTHOR: Jordi Trubat.
 COPYRIGHT: Copyright (C) 2016 Free Software Foundation, Inc. <http://fsf.org/>
 This is free software with ABSOLUTELY NO WARRANTY.
*/
#include "easter.h"

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

