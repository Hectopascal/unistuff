#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


int printWondrous (unsigned long long input);


int main(int argc, char *argv[])
{   
    int length;
    int check = 0;
    int largest = 0;
    unsigned long long x = 1341234558;
    while(check == 0){
        length = printWondrous(x);
        if(length>1234){
            check = 1;
            printf("%llu\n", x);
        } else if(length > largest){
            printf("%d %llu\n", length, x);
            largest = length;
  
        } 
        
        x++;

    }


    return 0;
}

int printWondrous (unsigned long long input) {
    unsigned long long start = input;
    int counter = 1;
    unsigned long long final;
    if (start == 1){
        final = start;

    } else {
        while(start != 1){
            
            if(start % 2 == 0){
                
                final = start/2;

            } else {

                final = start*3 + 1;

            }
        counter++;
        start = final;
        }
    }
    return (counter);
}
