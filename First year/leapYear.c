//by Ng Yi Yan waisquare z5013079
//T12A, Oliver Tan
//9 March 2015
// checks whether or not a year is a leap year

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define START_OF_GREG_CALENDAR 1582

int main (int argc, char * argv[]){
int year;

printf ("please enter the year you are interested in\n");

scanf ("%d", &year);

assert(year >= START_OF_GREG_CALENDAR);

if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
    printf ("%d is a leap year!\n",year);
    /*if (year % 400 == 0){
        printf ("%d is a leap year!\n",year);
    } else {
        if (year % 100 == 0){
            printf ("%d is not a leap year!\n",year);
        } else {
            printf ("%d is a leap year!\n",year);
        }
        }*/
    
} else{
    printf ("%d is not a leap year!\n",year);
}

return EXIT_SUCCESS;
}