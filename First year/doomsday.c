/*  Ng Yi Yan, z5013079
 *  T12A, Oliver Tan
 *  March 23, 2015
 *  doomsday.c
 *  A program to test a function dayOfWeek which determines which
 *  day of the week a particular date falls on.
 *  (only for dates after the start of the Gregorian calendar).
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
 
#define THURSDAY 0
#define FRIDAY   1
#define SATURDAY 2
#define SUNDAY   3
#define MONDAY   4
#define TUESDAY  5
#define WEDNESDAY 6

#define JANUARY 1
#define FEBRUARY 2
#define MARCH 3
#define APRIL 4
#define MAY 5
#define JUNE 6
#define JULY 7
#define AUGUST 8
#define SEPTEMBER 9
#define OCTOBER 10
#define NOVEMBER 11
#define DECEMBER 12
 
#define TRUE 1
#define FALSE 0
#define DAYS_PER_WEEK 7

#define lastDayFeb 28
#define lastDayLeapFeb 29
#define buffer 49

int dayOfWeek (int doomsday, int leapYear, int month, int day);
int leapAffected (int doomsday, int leapYear, int month, int day);

int main (int argc, char *argv[]) {
    //Testing some recent dates
    assert (dayOfWeek (THURSDAY, FALSE, 4, 4) == THURSDAY);
    assert (dayOfWeek (FRIDAY, FALSE, 6, 6) == FRIDAY);
    assert (dayOfWeek (MONDAY, FALSE, 8, 8) == MONDAY);
    assert (dayOfWeek (WEDNESDAY, FALSE, 10, 10) == WEDNESDAY);
    assert (dayOfWeek (FRIDAY, FALSE, 12, 12) == FRIDAY);
    assert (dayOfWeek (THURSDAY, FALSE, 9, 5) == THURSDAY);
    assert (dayOfWeek (FRIDAY, FALSE, 5, 9) == FRIDAY);
    assert (dayOfWeek (SUNDAY, FALSE, 7, 11) == SUNDAY);
    assert (dayOfWeek (SUNDAY, TRUE, 9, 9 ) == THURSDAY);
    assert (dayOfWeek (TUESDAY, FALSE, 11, 7) == TUESDAY);
    assert (dayOfWeek (WEDNESDAY, FALSE, 3, 7) == WEDNESDAY);
    assert (dayOfWeek (WEDNESDAY, TRUE, 9, 25) == TUESDAY);
    assert (dayOfWeek (THURSDAY, TRUE, 1, 3) == WEDNESDAY);
    assert (dayOfWeek (MONDAY, TRUE, 8, 22) == MONDAY);
    assert (dayOfWeek (SUNDAY, FALSE, 10, 8) == FRIDAY);
    assert (dayOfWeek (SATURDAY, FALSE, 3, 12) == THURSDAY);
    assert (dayOfWeek (SATURDAY, FALSE, 7, 1) == WEDNESDAY);
    assert (dayOfWeek (THURSDAY, TRUE, 3, 30) == SATURDAY);
    assert (dayOfWeek (THURSDAY, TRUE, 1, 3) == WEDNESDAY);
    
    
    //JANUARY leap year testing
    printf ("Testing January Leap Year\n");
    assert (dayOfWeek (MONDAY, FALSE, 1, 1) == SATURDAY);
    assert (dayOfWeek (MONDAY, FALSE, 1, 29) == SATURDAY);
    assert (dayOfWeek (MONDAY, FALSE, 1, 31) == MONDAY);
    assert (dayOfWeek (MONDAY, TRUE, 1, 1) == FRIDAY);
    assert (dayOfWeek (MONDAY, TRUE, 1, 29) == FRIDAY);
    assert (dayOfWeek (MONDAY, TRUE, 1, 31) == SUNDAY);
    assert (dayOfWeek (WEDNESDAY, FALSE, 1, 1) == MONDAY);
    assert (dayOfWeek (WEDNESDAY, FALSE, 1, 29) == MONDAY);
    assert (dayOfWeek (WEDNESDAY, FALSE, 1, 31) == WEDNESDAY);
    assert (dayOfWeek (WEDNESDAY, TRUE, 1, 1) == SUNDAY);
    assert (dayOfWeek (WEDNESDAY, TRUE, 1, 29) == SUNDAY);
    assert (dayOfWeek (WEDNESDAY, TRUE, 1, 31) == TUESDAY);


    // Test cases further than one week behind doomsday
    printf("Testing > 1 week before Doomsday\n");
    assert (dayOfWeek (SATURDAY, FALSE, 12, 1) == TUESDAY);
    assert (dayOfWeek (SATURDAY, FALSE, 10, 1) == THURSDAY);


    // Test multiples of 7 days (weeks) ahead of a doomsday
    assert (dayOfWeek (MONDAY, FALSE, 1, 10) == MONDAY);
    assert (dayOfWeek (TUESDAY, FALSE, 2, 14) == TUESDAY);
    assert (dayOfWeek (WEDNESDAY, FALSE, 3, 14) == WEDNESDAY);
    assert (dayOfWeek (THURSDAY, FALSE, 4, 18) == THURSDAY);
    assert (dayOfWeek (FRIDAY, FALSE, 5, 16) == FRIDAY);
    assert (dayOfWeek (SATURDAY, FALSE, 6, 20) == SATURDAY);
    assert (dayOfWeek (SUNDAY, FALSE, 7, 18) == SUNDAY);
    assert (dayOfWeek (MONDAY, FALSE, 8, 22) == MONDAY);
    assert (dayOfWeek (TUESDAY, FALSE, 9, 26) == TUESDAY);
    assert (dayOfWeek (WEDNESDAY, FALSE, 10, 17) == WEDNESDAY);
    assert (dayOfWeek (THURSDAY, FALSE, 11, 28) == THURSDAY);
    assert (dayOfWeek (FRIDAY, FALSE, 12, 19) == FRIDAY);


    /// Test one week ahead
    printf("Testing > 1 week after Doomsday\n");
    assert (dayOfWeek (FRIDAY, FALSE, 6, 30) == MONDAY);
    assert (dayOfWeek (FRIDAY, FALSE, 6, 13) == FRIDAY);


    // First day of each month
    printf("Testing first day of each month\n");
    assert (dayOfWeek (MONDAY, FALSE, 1, 1) == SATURDAY);
    assert (dayOfWeek (MONDAY, FALSE, 2, 1) == TUESDAY);
    assert (dayOfWeek (MONDAY, FALSE, 3, 1) == TUESDAY);
    assert (dayOfWeek (MONDAY, FALSE, 4, 1) == FRIDAY);
    assert (dayOfWeek (MONDAY, FALSE, 5, 1) == SUNDAY);
    assert (dayOfWeek (MONDAY, FALSE, 6, 1) == WEDNESDAY);
    assert (dayOfWeek (MONDAY, FALSE, 7, 1) == FRIDAY);
    assert (dayOfWeek (MONDAY, FALSE, 8, 1) == MONDAY);
    assert (dayOfWeek (MONDAY, FALSE, 9, 1) == THURSDAY);
    assert (dayOfWeek (MONDAY, FALSE, 10, 1) == SATURDAY);
    assert (dayOfWeek (MONDAY, FALSE, 11, 1) == TUESDAY);
    assert (dayOfWeek (MONDAY, FALSE, 12, 1) == THURSDAY);
    assert (dayOfWeek (MONDAY, TRUE, 1, 1) == FRIDAY);
    assert (dayOfWeek (MONDAY, TRUE, 2, 1) == MONDAY);
    
   // Last day of each month
    printf("Testing last day of each month\n");
    assert (dayOfWeek (MONDAY, FALSE, 1, 31) == MONDAY);
    assert (dayOfWeek (MONDAY, FALSE, 2, 28) == MONDAY);
    assert (dayOfWeek (MONDAY, FALSE, 3, 31) == THURSDAY);
    assert (dayOfWeek (MONDAY, FALSE, 4, 30) == SATURDAY);
    assert (dayOfWeek (MONDAY, FALSE, 5, 31) == TUESDAY);
    assert (dayOfWeek (MONDAY, FALSE, 6, 30) == THURSDAY);
    assert (dayOfWeek (MONDAY, FALSE, 7, 31) == SUNDAY);
    assert (dayOfWeek (MONDAY, FALSE, 8, 31) == WEDNESDAY);
    assert (dayOfWeek (MONDAY, FALSE, 9, 30) == FRIDAY);
    assert (dayOfWeek (MONDAY, FALSE, 10, 31) == MONDAY);
    assert (dayOfWeek (MONDAY, FALSE, 11, 30) == WEDNESDAY);
    assert (dayOfWeek (MONDAY, FALSE, 12, 31) == SATURDAY);
    assert (dayOfWeek (MONDAY, TRUE, 1, 31) == SUNDAY);
    assert (dayOfWeek (MONDAY, TRUE, 2, 29) == MONDAY);
    
    
   //One day before doomsday
   printf("Testing one day before doomsday of each relevant month\n");
   assert (dayOfWeek (THURSDAY, TRUE, 2, 28) == WEDNESDAY);
   assert (dayOfWeek (THURSDAY, FALSE, 2, 27) == WEDNESDAY);
   assert (dayOfWeek (THURSDAY, FALSE, 4, 3) == WEDNESDAY);
   assert (dayOfWeek (THURSDAY, FALSE, 5, 8) == WEDNESDAY);
   assert (dayOfWeek (THURSDAY, FALSE, 6, 5) == WEDNESDAY);
   assert (dayOfWeek (THURSDAY, FALSE, 7, 10) == WEDNESDAY);
   assert (dayOfWeek (THURSDAY, FALSE, 8, 7) == WEDNESDAY);
   assert (dayOfWeek (THURSDAY, FALSE, 9, 4) == WEDNESDAY);
   assert (dayOfWeek (THURSDAY, FALSE, 10, 9) == WEDNESDAY);
   assert (dayOfWeek (THURSDAY, FALSE, 11, 6) == WEDNESDAY);
   assert (dayOfWeek (THURSDAY, FALSE, 12, 11) == WEDNESDAY);
    
    
   //just a test
   printf("Just a test.\n");
   assert (dayOfWeek (FRIDAY, FALSE, 11, 9) == SUNDAY);
    
    
   //Test Christmas Day and Boxing Day
   assert (dayOfWeek (SATURDAY, FALSE, 12, 25) == FRIDAY);
   assert (dayOfWeek (SATURDAY, FALSE, 12, 26) == SATURDAY);
 
   
   //More Christmas Days
   assert (dayOfWeek (SATURDAY, FALSE, 12, 25) == FRIDAY);
   assert (dayOfWeek (FRIDAY, FALSE, 12, 25) == THURSDAY);
   assert (dayOfWeek (THURSDAY, FALSE, 12, 25) == WEDNESDAY);
   assert (dayOfWeek (WEDNESDAY, FALSE, 12, 25) == TUESDAY);
   assert (dayOfWeek (MONDAY, FALSE, 12, 25) == SUNDAY);
    

   // Test Pi Day for every day!
   assert (dayOfWeek (THURSDAY, FALSE, 3, 14) == THURSDAY);
   assert (dayOfWeek (FRIDAY, FALSE, 3, 14) == FRIDAY);
   assert (dayOfWeek (SATURDAY, FALSE, 3, 14) == SATURDAY);
   assert (dayOfWeek (SUNDAY, FALSE, 3, 14) == SUNDAY);
   assert (dayOfWeek (MONDAY, FALSE, 3, 14) == MONDAY);
   assert (dayOfWeek (TUESDAY, FALSE, 3, 14) == TUESDAY);
   assert (dayOfWeek (WEDNESDAY, FALSE, 3, 14) == WEDNESDAY);
    
     // Testing birthday
   assert (dayOfWeek (SATURDAY, FALSE, 4, 5) == SUNDAY);
   
   // Judgement Day
   assert (dayOfWeek (FRIDAY, FALSE, 8, 29) == FRIDAY);
   assert (dayOfWeek (SUNDAY, TRUE, 7, 25) == SUNDAY);
 
 
   // Some random dates
   assert (dayOfWeek (THURSDAY, FALSE, 2, 2) == SATURDAY);
   assert (dayOfWeek (THURSDAY, FALSE, 4, 20) == SATURDAY);
   assert (dayOfWeek (FRIDAY, FALSE, 7, 20) == SUNDAY);
   assert (dayOfWeek (THURSDAY, FALSE, 5, 10) == FRIDAY);
   assert (dayOfWeek (THURSDAY, FALSE, 12, 25) == WEDNESDAY);
 
 
   // Testing my birthday 1997 and Tau Day 2015
   assert (dayOfWeek (FRIDAY, FALSE, 2, 11) == TUESDAY);
   assert (dayOfWeek (SATURDAY, FALSE, 6, 28) == SUNDAY);
 
   // Really, the best country in the world is ICELAND
   // So is the date of the 2014 - 2015 Icelandic independence day
   // By Nicholas Joaquin
    assert (dayOfWeek (SATURDAY, FALSE, 6, 17) == WEDNESDAY);
    assert (dayOfWeek (FRIDAY, FALSE, 6, 17) == TUESDAY);
 
   // Dates all the star wars movies were released
    assert (dayOfWeek (MONDAY, FALSE, 5, 25) == WEDNESDAY);
    assert (dayOfWeek (FRIDAY, TRUE, 5, 21) == WEDNESDAY);
    assert (dayOfWeek (MONDAY, FALSE, 5, 25) == WEDNESDAY);
    assert (dayOfWeek (SUNDAY, FALSE, 5, 19) == WEDNESDAY);
    assert (dayOfWeek (THURSDAY, FALSE, 5, 16) == THURSDAY);
    assert (dayOfWeek (MONDAY, FALSE, 5, 19) == THURSDAY);
    assert (dayOfWeek (SATURDAY, FALSE, 12, 18) == FRIDAY);
 
   // Yet another set of random date
    assert (dayOfWeek (SATURDAY, FALSE, 3, 25) == WEDNESDAY);
    assert (dayOfWeek (SATURDAY, FALSE, 5, 22) == FRIDAY);
    assert (dayOfWeek (SATURDAY, FALSE, 7, 31) == FRIDAY);
    assert(dayOfWeek(SATURDAY, FALSE, 3, 26) == THURSDAY);

    assert(dayOfWeek(SATURDAY, FALSE, 3, 27) == FRIDAY);

     

    assert (dayOfWeek (THURSDAY, TRUE, 4, 6) == SATURDAY);

    assert (dayOfWeek (SATURDAY, FALSE, 7, 12) == SUNDAY);

    assert (dayOfWeek (SUNDAY, FALSE, 1,10) == SUNDAY);

    assert (dayOfWeek (SATURDAY, FALSE, 12, 14) == MONDAY);

     

    // In 2016

    assert (dayOfWeek ( MONDAY, TRUE, 4, 6) == WEDNESDAY);

    assert (dayOfWeek ( MONDAY, TRUE, 6, 9) == THURSDAY);

    assert (dayOfWeek ( MONDAY, TRUE, 8, 13) == SATURDAY);

// The date of our first lecture

    assert (dayOfWeek (SATURDAY, FALSE, 3, 2) == MONDAY);

    assert (dayOfWeek (THURSDAY, FALSE, 1, 17) == THURSDAY); 
    assert (dayOfWeek (WEDNESDAY, FALSE, 2, 21) == WEDNESDAY); 
    assert (dayOfWeek (FRIDAY, FALSE, 3, 21) == FRIDAY); 
    assert (dayOfWeek (SATURDAY, FALSE, 4, 25) == SATURDAY); 
    assert (dayOfWeek (SUNDAY, FALSE, 5, 23) == SUNDAY); 
    assert (dayOfWeek (MONDAY, FALSE, 6, 27) ==MONDAY);
    assert (dayOfWeek (TUESDAY, FALSE, 7, 25) == TUESDAY);
    assert (dayOfWeek (WEDNESDAY, FALSE, 8, 29) == WEDNESDAY);
    assert (dayOfWeek (THURSDAY, FALSE, 11, 21) == THURSDAY);
    assert (dayOfWeek (WEDNESDAY, FALSE, 12, 26) == WEDNESDAY);

    assert (dayOfWeek(THURSDAY, TRUE, 1, 11) == THURSDAY); 
    assert (dayOfWeek (WEDNESDAY, TRUE, 2, 22) == WEDNESDAY); 
    assert (dayOfWeek (SATURDAY, TRUE, 4, 25) == SATURDAY); 
    assert (dayOfWeek (SUNDAY, TRUE, 5, 23) == SUNDAY); 
    assert (dayOfWeek (MONDAY, TRUE, 6, 27) ==MONDAY);
 
    //Testing when the day falls on the anchor day for each month, 
    //on leap years and non leap years
    assert (dayOfWeek (THURSDAY, FALSE, 1, 3) == THURSDAY);
    assert (dayOfWeek (THURSDAY, TRUE, 1, 4) == THURSDAY);
    assert (dayOfWeek (THURSDAY, FALSE, 2, 14) == THURSDAY);
    assert (dayOfWeek (THURSDAY, TRUE, 2, 22) == THURSDAY);
    assert (dayOfWeek (THURSDAY, FALSE, 3, 14) == THURSDAY);
    assert (dayOfWeek (THURSDAY, TRUE, 3, 14) == THURSDAY);
    assert (dayOfWeek (THURSDAY, FALSE, 4, 4) == THURSDAY);
    assert (dayOfWeek (THURSDAY, TRUE, 4, 4) == THURSDAY);
    assert (dayOfWeek (THURSDAY, FALSE, 5, 9) == THURSDAY);
    assert (dayOfWeek (THURSDAY, TRUE, 5, 9) == THURSDAY);
    assert (dayOfWeek (THURSDAY, FALSE, 6, 6) == THURSDAY);
    assert (dayOfWeek (THURSDAY, TRUE, 6, 6) == THURSDAY);
    assert (dayOfWeek (THURSDAY, FALSE, 7, 11) == THURSDAY);
    assert (dayOfWeek (THURSDAY, TRUE, 7, 11) == THURSDAY);
    assert (dayOfWeek (THURSDAY, FALSE, 8, 8) == THURSDAY);
    assert (dayOfWeek (THURSDAY, TRUE, 8, 8) == THURSDAY);
    assert (dayOfWeek (THURSDAY, FALSE, 9, 5) == THURSDAY);
    assert (dayOfWeek (THURSDAY, TRUE, 9, 5) == THURSDAY);
    assert (dayOfWeek (THURSDAY, FALSE, 10, 10) == THURSDAY);
    assert (dayOfWeek (THURSDAY, TRUE, 10, 10) == THURSDAY);
    assert (dayOfWeek (THURSDAY, FALSE, 11, 7) == THURSDAY);
    assert (dayOfWeek (THURSDAY, TRUE, 11, 7) == THURSDAY);
    assert (dayOfWeek (THURSDAY, FALSE, 12, 12) == THURSDAY);
    assert (dayOfWeek (THURSDAY, TRUE, 12, 12) == THURSDAY);
 
   
 
    //Test the doomsdays in 2015
    assert (dayOfWeek (SATURDAY, FALSE, 3, 14) == SATURDAY);
    assert (dayOfWeek (SATURDAY, FALSE, 4, 4) == SATURDAY);
    assert (dayOfWeek (SATURDAY, FALSE, 6, 6) == SATURDAY);
    assert (dayOfWeek (SATURDAY, FALSE, 10, 10) == SATURDAY);
    assert (dayOfWeek (SATURDAY, FALSE, 12, 12) == SATURDAY);
    assert (dayOfWeek (SATURDAY, FALSE, 9, 5) == SATURDAY);
    assert (dayOfWeek (SATURDAY, FALSE, 5, 9) == SATURDAY);
    assert (dayOfWeek (SATURDAY, FALSE, 11, 7) == SATURDAY);
    assert (dayOfWeek (SATURDAY, FALSE, 7, 11) == SATURDAY);
 
    //test the 29th of feb in various years
    assert (dayOfWeek (MONDAY, TRUE, 2, 29) == MONDAY); //2016
    assert (dayOfWeek (FRIDAY, TRUE, 2, 29) == FRIDAY); //2008
    assert (dayOfWeek (SUNDAY, TRUE, 2, 29) == SUNDAY); //2004
    assert (dayOfWeek (TUESDAY, TRUE, 2, 29) == TUESDAY); //2000
    assert (dayOfWeek (SATURDAY, TRUE, 2, 29) == SATURDAY); //1936
    assert (dayOfWeek (WEDNESDAY, TRUE, 2, 29) == WEDNESDAY); //1928
 
   //Test my birthday 2000, 2002, 2004, 2008, and 2012
    assert (dayOfWeek (TUESDAY, TRUE, 8, 10) == THURSDAY); //2000
    assert (dayOfWeek (THURSDAY, FALSE, 8, 10) == SATURDAY); //2002
    assert (dayOfWeek (SUNDAY, TRUE, 8, 10) == TUESDAY); //2004
    assert (dayOfWeek (FRIDAY, TRUE, 8, 10) == SUNDAY); //2008
    assert (dayOfWeek (WEDNESDAY, TRUE, 8, 10) == FRIDAY); //2012

    assert (dayOfWeek (WEDNESDAY,  FALSE,  7, 7) == SATURDAY);
    assert (dayOfWeek (WEDNESDAY,  TRUE,  7, 7) == SATURDAY);
    assert (dayOfWeek (THURSDAY,  FALSE,  7, 7) == SUNDAY);
    assert (dayOfWeek (THURSDAY,  TRUE,  7, 7) == SUNDAY);

// Test all days of the week
    assert (dayOfWeek (MONDAY,    FALSE, 7, 11) == MONDAY );
    assert (dayOfWeek (TUESDAY,   FALSE, 7, 11) == TUESDAY );
    assert (dayOfWeek (WEDNESDAY, FALSE, 7, 11) == WEDNESDAY );
    assert (dayOfWeek (THURSDAY,  FALSE, 7, 11) == THURSDAY );
    assert (dayOfWeek (FRIDAY,    FALSE, 7, 11) == FRIDAY );
    assert (dayOfWeek (SATURDAY,  FALSE, 7, 11) == SATURDAY );
    assert (dayOfWeek (SUNDAY,    FALSE, 7, 11) == SUNDAY );
 
    assert (dayOfWeek (TUESDAY,   TRUE, 7, 11) == TUESDAY );
    assert (dayOfWeek (WEDNESDAY, TRUE, 7, 11) == WEDNESDAY );
    assert (dayOfWeek (THURSDAY,  TRUE, 7, 11) == THURSDAY );
    assert (dayOfWeek (FRIDAY,    TRUE, 7, 11) == FRIDAY );
    assert (dayOfWeek (SATURDAY,  TRUE, 7, 11) == SATURDAY );
    assert (dayOfWeek (SUNDAY,    TRUE, 7, 11) == SUNDAY );
    assert (dayOfWeek (THURSDAY,  FALSE,  4,  4) == THURSDAY);
    assert (dayOfWeek (FRIDAY,    FALSE,  6,  6) == FRIDAY);
    assert (dayOfWeek (MONDAY,    FALSE,  8,  8) == MONDAY);
    assert (dayOfWeek (WEDNESDAY, FALSE, 10, 10) == WEDNESDAY);
    assert (dayOfWeek (FRIDAY,    FALSE, 12, 12) == FRIDAY);
    assert (dayOfWeek (THURSDAY,  FALSE,  9,  5) == THURSDAY);
    assert (dayOfWeek (FRIDAY,    FALSE,  5,  9) == FRIDAY);
    assert (dayOfWeek (SUNDAY,    FALSE,  7, 11) == SUNDAY);
    assert (dayOfWeek (TUESDAY,   FALSE, 11,  7) == TUESDAY);
    assert (dayOfWeek (WEDNESDAY, FALSE,  3,  7) == WEDNESDAY);
 
    assert (dayOfWeek (THURSDAY,  FALSE,  4,  5) == FRIDAY);
    assert (dayOfWeek (SATURDAY,  FALSE,  6,  5) == FRIDAY);
    assert (dayOfWeek (MONDAY,    FALSE,  8,  9) == TUESDAY);
    assert (dayOfWeek (WEDNESDAY, FALSE, 10,  9) == TUESDAY);
    assert (dayOfWeek (FRIDAY,    FALSE, 12, 20) == SATURDAY);
    assert (dayOfWeek (THURSDAY,  FALSE,  9,  9) == MONDAY);
    assert (dayOfWeek (FRIDAY,    FALSE,  5,  5) == MONDAY);
    assert (dayOfWeek (SUNDAY,    FALSE,  7,  7) == WEDNESDAY);
    assert (dayOfWeek (TUESDAY,   FALSE, 11, 11) == SATURDAY);
    assert (dayOfWeek (THURSDAY,  FALSE,  3, 30) == SATURDAY);
 
    assert (dayOfWeek (TUESDAY,   FALSE,  2,  28) == TUESDAY);
    assert (dayOfWeek (TUESDAY,   FALSE,  2,  27) == MONDAY);
    assert (dayOfWeek (THURSDAY,  FALSE,  1,  3)  == THURSDAY);
 
    printf ("all tests passed - You are awesome!\n");
    return EXIT_SUCCESS;
}
 
 
// given the doomsday for a year, and whether or not it is a
// leap year, this function return the day of the week for any
// given month and day in the year.
 
int dayOfWeek (int doomsday, int leapYear, int month, int day) {
    int dayOfWeek;
    int anchor; //doomsday date in every month
    if(month != FEBRUARY && (month % 2) == 0){
        //even months excluding Feb
        dayOfWeek = ((doomsday + day - month + buffer) % DAYS_PER_WEEK);
        //buffer ensures dayOfWeek is positive
    } else if(month == MARCH){
        anchor = 0;
        dayOfWeek = (doomsday + day - anchor + buffer) % DAYS_PER_WEEK;       

    } else if (month == MAY) {
        anchor = 9;
        dayOfWeek = (doomsday + day - anchor + buffer) % DAYS_PER_WEEK;

    } else if (month == JULY) {
        anchor = 11;
        dayOfWeek = (doomsday + day - anchor + buffer) % DAYS_PER_WEEK;

    } else if (month == SEPTEMBER) {
        anchor = 5;
        dayOfWeek = (doomsday + day - anchor + buffer) % DAYS_PER_WEEK;
        
    } else if (month == NOVEMBER) {
        anchor = 7;
        dayOfWeek = (doomsday + day - anchor + buffer) % DAYS_PER_WEEK;
        
    } else {
        //january and february
        dayOfWeek = leapAffected(doomsday, leapYear, month, day);

    }

   return (dayOfWeek);
}

int leapAffected (int doomsday, int leapYear, int month, int day){
    int anchor;
    int dayOfWeek;
    if(leapYear == 0){

        if(month == JANUARY){
            anchor = 3;
            dayOfWeek = (doomsday + day - anchor + buffer) % DAYS_PER_WEEK;
        } else {
            dayOfWeek = (doomsday + day - lastDayFeb + buffer) % DAYS_PER_WEEK;
        }

    } else {

        if(month == JANUARY){
            anchor = 4;
            dayOfWeek = (doomsday + day - anchor + buffer) % DAYS_PER_WEEK;
        } else {
            dayOfWeek = (doomsday + day - lastDayLeapFeb + buffer) % DAYS_PER_WEEK;
        }

    }
    return (dayOfWeek);
}
