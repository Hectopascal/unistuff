#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


unsigned long long printWondrous (unsigned long long start);


int main(int argc, char *argv[])
{
    unsigned long long x;
    unsigned long long length;
    scanf("%llu/n", &x);

    length = printWondrous(x);
    printf("%llu\n", length);
    return 0;
}

unsigned long long printWondrous (unsigned long long start) {

    unsigned long long counter = 1;
    unsigned long long final;
    if (start == 1){
        final = start;
        printf("%llu", start);

    } else {
        printf("%llu ", start);
        while(start != 1){
            counter++;
            if(start % 2 == 0){
                
                final = start/2;

                if(final != 1){
                    printf("%llu ", final);
                } else{
                    printf("%llu", final);
                }

            } else {

                final = start*3 + 1;
                if(final != 1){
                    printf("%llu ", final);
                } else{
                    printf("%llu", final);
                }

            }
        start = final;

        }
    }
    printf("\n");
    return (counter);
}
