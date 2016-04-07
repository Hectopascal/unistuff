//by Ng Yi Yan waisquare z5013079
//T12A, Oliver Tan
//9 March 2015
//runs a function that checks whether or not a year is a leap year
/* Test cases:
Year  Leap year?
4000  yes
4004  yes
1999  no
1900  no
2000  yes
1904  yes
2015  no
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define START_OF_GREG_CALENDAR 1582

int isLeapYear (int year) {
    if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        return 1;
    } else{
        return 0;
    }
}
int main (int argc, char * argv[]){
    int year;
    
    printf ("please enter a year after 1582\n");
    scanf("%d", &year);
    int isLeap = isLeapYear(year);
    if (isLeap == 1){
        printf("%d is a leap year!\n",year);
    } else{
        printf("%d is not a leap year!\n",year);
    }

    return EXIT_SUCCESS;
}

